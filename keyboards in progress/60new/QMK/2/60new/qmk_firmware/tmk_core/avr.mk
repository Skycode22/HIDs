# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Compiler settings
#
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar rcs
NM = avr-nm
HEX = $(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature
EEP = $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) 
BIN =



COMPILEFLAGS += -funsigned-char
COMPILEFLAGS += -funsigned-bitfields
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fpack-struct
COMPILEFLAGS += -fshort-enums

CFLAGS += $(COMPILEFLAGS)
CFLAGS += -fno-inline-small-functions
CFLAGS += -fno-strict-aliasing

CPPFLAGS += $(COMPILEFLAGS)
CPPFLAGS += -fno-exceptions -std=c++11

LDFLAGS +=-Wl,--gc-sections

OPT_DEFS += -DF_CPU=$(F_CPU)UL

MCUFLAGS = -mmcu=$(MCU)

# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRALIBDIRS =


#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =

#---------------- Debugging Options ----------------

# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2

# For simulavr only - target MCU frequency.
DEBUG_MFREQ = $(F_CPU)

# Set the DEBUG_UI to either gdb or insight.
# DEBUG_UI = gdb
DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# GDB Init Filename.
GDBINIT_FILE = __avr_gdbinit

# When using avarice settings for the JTAG
JTAG_DEV = /dev/com1

# Debugging port used to communicate between GDB / avarice / simulavr.
DEBUG_PORT = 4242

# Debugging host used to communicate between GDB / avarice / simulavr, normally
#     just set to localhost unless doing some sort of crazy debugging when
#     avarice is running on a different computer.
DEBUG_HOST = localhost

#============================================================================
# Autodecct teensy loader
ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
  TEENSY_LOADER_CLI = teensy-loader-cli
else
  TEENSY_LOADER_CLI = teensy_loader_cli
endif

# Program the device.
program: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	$(PROGRAM_CMD)

teensy: $(BUILD_DIR)/$(TARGET).hex
	$(TEENSY_LOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex

flip: $(BUILD_DIR)/$(TARGET).hex
	batchisp -hardware usb -device $(MCU) -operation erase f
	batchisp -hardware usb -device $(MCU) -operation loadbuffer $(BUILD_DIR)/$(TARGET).hex program
	batchisp -hardware usb -device $(MCU) -operation start reset 0

dfu: $(BUILD_DIR)/$(TARGET).hex sizeafter
	until dfu-programmer $(MCU) get bootloader-version; do\
		echo "Error: Bootloader not found. Trying again in 5s." ;\
		sleep 5 ;\
	done
ifneq (, $(findstring 0.7, $(shell dfu-programmer --version 2>&1)))
	dfu-programmer $(MCU) erase --force
else
	dfu-programmer $(MCU) erase
endif
	dfu-programmer $(MCU) flash $(BUILD_DIR)/$(TARGET).hex
	dfu-programmer $(MCU) reset

dfu-start:
	dfu-programmer $(MCU) reset
	dfu-programmer $(MCU) start

flip-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	$(COPY) $(BUILD_DIR)/$(TARGET).eep $(BUILD_DIR)/$(TARGET)eep.hex
	batchisp -hardware usb -device $(MCU) -operation memory EEPROM erase
	batchisp -hardware usb -device $(MCU) -operation memory EEPROM loadbuffer $(BUILD_DIR)/$(TARGET)eep.hex program
	batchisp -hardware usb -device $(MCU) -operation start reset 0
	$(REMOVE) $(BUILD_DIR)/$(TARGET)eep.hex

dfu-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
ifneq (, $(findstring 0.7, $(shell dfu-programmer --version 2>&1)))
	dfu-programmer $(MCU) flash --eeprom $(BUILD_DIR)/$(TARGET).eep
else
	dfu-programmer $(MCU) flash-eeprom $(BUILD_DIR)/$(TARGET).eep
endif
	dfu-programmer $(MCU) reset

# Convert hex to bin.
flashbin: $(BUILD_DIR)/$(TARGET).hex
	$(OBJCOPY) -Iihex -Obinary $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;
	$(COPY) $(BUILD_DIR)/$(TARGET).bin FLASH.bin; 

# Generate avr-gdb config/init file which does the following:
#     define the reset signal, load the target file, connect to target, and set
#     a breakpoint at main().
gdb-config:
	@$(REMOVE) $(GDBINIT_FILE)
	@echo define reset >> $(GDBINIT_FILE)
	@echo SIGNAL SIGHUP >> $(GDBINIT_FILE)
	@echo end >> $(GDBINIT_FILE)
	@echo file $(BUILD_DIR)/$(TARGET).elf >> $(GDBINIT_FILE)
	@echo target remote $(DEBUG_HOST):$(DEBUG_PORT)  >> $(GDBINIT_FILE)
ifeq ($(DEBUG_BACKEND),simulavr)
	@echo load  >> $(GDBINIT_FILE)
endif
	@echo break main >> $(GDBINIT_FILE)

debug: gdb-config $(BUILD_DIR)/$(TARGET).elf
ifeq ($(DEBUG_BACKEND), avarice)
	@echo Starting AVaRICE - Press enter when "waiting to connect" message displays.
	@$(WINSHELL) /c start avarice --jtag $(JTAG_DEV) --erase --program --file \
	$(BUILD_DIR)/$(TARGET).elf $(DEBUG_HOST):$(DEBUG_PORT)
	@$(WINSHELL) /c pause

else
	@$(WINSHELL) /c start simulavr --gdbserver --device $(MCU) --clock-freq \
	$(DEBUG_MFREQ) --port $(DEBUG_PORT)
endif
	@$(WINSHELL) /c start avr-$(DEBUG_UI) --command=$(GDBINIT_FILE)




# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000



coff: $(BUILD_DIR)/$(TARGET).elf
	@$(SECHO) $(MSG_COFF) $(BUILD_DIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(BUILD_DIR)/$(TARGET).cof


extcoff: $(BUILD_DIR)/$(TARGET).elf
	@$(SECHO) $(MSG_EXTENDED_COFF) $(BUILD_DIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(BUILD_DIR)/$(TARGET).cof


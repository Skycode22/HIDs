# Winry25tc MIDI note/CC mode firmware

[Winry25tc](https://ae01.alicdn.com/kf/Hf82e3c6dde4541eea65d1dd42b69cbcfE.jpg)

*MIDI mode for winry25tc*

* Variants
    * In MIDI note variation all of buttons mapped to midi notes: from C/48 (90 30 XX) to D2/74 (80 4A XX)
    * In MIDI CC variation all of buttons mapped to CC 1 (B0 01 XX) through 25 (B0 19 XX)

* Keyboard Maintainer: [Kostiantyn Yerokhin](https://github.com/err5)
* Hardware Supported: Winry25tc (SpiderIsland's 5x5 MacroPad)
* Hardware Availability: https://www.aliexpress.com/item/1005002559266513.html?spm=a2g0o

Building:
   
*  To get MIDI note variation:
    ```qmk compile -kb winry25_midi -km note```
*  To get MIDI CC variation:
    ```qmk compile -kb winry25_midi -km cc```

Flashing is done via [qmk_toolbox](https://github.com/qmk/qmk_toolbox)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

In order to flash firmware you need to enter bootloader mode
* **Physical reset button**: Briefly press the button on the back of the PCB twice

/*****************************************************************************
* | File      	:   Readme_EN.txt
* | Author      :   
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :   Here is an English version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this routine.
Here is a brief description of the use of this project:

1. Basic information:
This routine has been verified using the corresponding module with Pico, 
you can view the corresponding test routine in the project;

2. Pin connection:
You can check the pin connection at Pico-LCD-1.3.py, and repeat it here:
LCD 1.3 
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13
A       ->   15
B       ->    17
X       ->    19
Y       ->    21
UP     ->    2
DOWM ->    18
LEFT   ->    16
RIGHT ->    20
CTRL  ->    3


3. Basic use:
    1): Press and hold the button on the Pico board, connect Pico to the USB port of the 
        computer through the Micro USB cable, and then release the button.
        After connecting, the computer will automatically recognize a removable disk (RPI-RP2)
        
    2): Copy the pico_micropython_20210121.uf2 file in the python directory to the recognized 
        removable disk (RPI-RP2)
    
    3): Update Thonny IDE
        sudo apt upgrade thonny
        
    4): Open Thonny IDE （Click raspberry logo -> Programming -> Thonny Python IDE ）
        select Tools -> Options... -> Interpreter
        select MicroPython(Raspberry Pi Pico  and ttyACM0 port
        
    5): Open the python/Pico-LCD-1.3/Pico-LCD-1.3.py file in Thonny IDE
        Then run the current script (green triangle)
    
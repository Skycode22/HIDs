
from machine import Pin,SPI,PWM
import framebuf
import time
import os

BL = 13
DC = 16
RST = 12
MOSI = 11
SCK = 10
CS = 17


class LCD_1inch3(framebuf.FrameBuffer):
    def __init__(self):
        self.width = 240
        self.height = 240
        
        self.cs = Pin(CS,Pin.OUT)
        self.rst = Pin(RST,Pin.OUT)
        
        self.cs(1)
        self.spi = SPI(1)
        self.spi = SPI(1,1000_000)
        self.spi = SPI(1,100000_000,polarity=0, phase=0,sck=Pin(SCK),mosi=Pin(MOSI),miso=None)
        self.dc = Pin(DC,Pin.OUT)
        self.dc(1)
        self.buffer = bytearray(self.height * self.width) #Due to insufficient memory, the screen is displayed twice
        super().__init__(self.buffer, self.width, self.height, framebuf.RGB565)
        self.init_display()
        
        self.red   =   0x07E0
        self.green =   0x001f
        self.blue  =   0xf800
        self.white =   0xffff
        
    def write_cmd(self, cmd):
        self.cs(1)
        self.dc(0)
        self.cs(0)
        self.spi.write(bytearray([cmd]))
        self.cs(1)

    def write_data(self, buf):
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(bytearray([buf]))
        self.cs(1)

    def init_display(self):
        """Initialize dispaly"""  
        self.rst(1)
        self.rst(0)
        self.rst(1)
        
        self.write_cmd(0x36)
        self.write_data(0x70)

        self.write_cmd(0x3A) 
        self.write_data(0x05)

        self.write_cmd(0xB2)
        self.write_data(0x0C)
        self.write_data(0x0C)
        self.write_data(0x00)
        self.write_data(0x33)
        self.write_data(0x33)

        self.write_cmd(0xB7)
        self.write_data(0x35) 

        self.write_cmd(0xBB)
        self.write_data(0x19)

        self.write_cmd(0xC0)
        self.write_data(0x2C)

        self.write_cmd(0xC2)
        self.write_data(0x01)

        self.write_cmd(0xC3)
        self.write_data(0x12)   

        self.write_cmd(0xC4)
        self.write_data(0x20)

        self.write_cmd(0xC6)
        self.write_data(0x0F) 

        self.write_cmd(0xD0)
        self.write_data(0xA4)
        self.write_data(0xA1)

        self.write_cmd(0xE0)
        self.write_data(0xD0)
        self.write_data(0x04)
        self.write_data(0x0D)
        self.write_data(0x11)
        self.write_data(0x13)
        self.write_data(0x2B)
        self.write_data(0x3F)
        self.write_data(0x54)
        self.write_data(0x4C)
        self.write_data(0x18)
        self.write_data(0x0D)
        self.write_data(0x0B)
        self.write_data(0x1F)
        self.write_data(0x23)

        self.write_cmd(0xE1)
        self.write_data(0xD0)
        self.write_data(0x04)
        self.write_data(0x0C)
        self.write_data(0x11)
        self.write_data(0x13)
        self.write_data(0x2C)
        self.write_data(0x3F)
        self.write_data(0x44)
        self.write_data(0x51)
        self.write_data(0x2F)
        self.write_data(0x1F)
        self.write_data(0x1F)
        self.write_data(0x20)
        self.write_data(0x23)
        
        self.write_cmd(0x21)

        self.write_cmd(0x11)

        self.write_cmd(0x29)

    def show(self,Xstart,Ystart,Xend,Yend):
        self.write_cmd(0x2A)
        self.write_data(0x00)
        self.write_data(Xstart & 0xFF)
        self.write_data(0x00)
        self.write_data((Xend - 1) & 0xFF)
        
        self.write_cmd(0x2B)
        self.write_data(0x00)
        self.write_data(Ystart & 0xFF)
        self.write_data(0x00)
        self.write_data((Yend - 1) & 0xFF)
        
        self.write_cmd(0x2C)
        
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(self.buffer)
        self.cs(1)

  
if __name__=='__main__':
    LCD = LCD_1inch3()
    #color BRG
    LCD.fill(LCD.white)
    LCD.show(0,0,240,120) #Show top half
    LCD.show(0,120,240,240) #Show bottom half

    keyA = Pin(15,Pin.IN,Pin.PULL_UP)
    keyB = Pin(17,Pin.IN,Pin.PULL_UP)
    keyX = Pin(19,Pin.IN,Pin.PULL_UP)
    keyY= Pin(21,Pin.IN,Pin.PULL_UP)
    
    up = Pin(2,Pin.IN,Pin.PULL_UP)
    dowm = Pin(18,Pin.IN,Pin.PULL_UP)
    left = Pin(16,Pin.IN,Pin.PULL_UP)
    right = Pin(20,Pin.IN,Pin.PULL_UP)
    ctrl = Pin(3,Pin.IN,Pin.PULL_UP)
    
    while(1):
        if keyA.value() == 0:
            LCD.fill_rect(208,15,30,30,LCD.red)
            print("A")
        else :
            LCD.fill_rect(208,15,30,30,LCD.white)
            LCD.rect(208,15,30,30,LCD.red)
                      
        if(keyB.value() == 0):
            LCD.fill_rect(208,75,30,30,LCD.red)
            print("B")
        else :
            LCD.fill_rect(208,75,30,30,LCD.white)
            LCD.rect(208,75,30,30,LCD.red)
                     
        if(up.value() == 0):
            LCD.fill_rect(60,70,30,30,LCD.red)
            print("UP")
        else :
            LCD.fill_rect(60,70,30,30,LCD.white)
            LCD.rect(60,70,30,30,LCD.red)
               
        LCD.show(0,0,240,120) #Show top half
        LCD.fill(LCD.white)
        
        if(keyX.value() == 0):
            LCD.fill_rect(208,15,30,30,LCD.red)
            print("C")
        else :
            LCD.fill_rect(208,15,30,30,LCD.white)
            LCD.rect(208,15,30,30,LCD.red)
            
        if(keyY.value() == 0):
            LCD.fill_rect(208,75,30,30,LCD.red)
            print("D")
        else :
            LCD.fill_rect(208,75,30,30,LCD.white)
            LCD.rect(208,75,30,30,LCD.red)
            
        if(dowm.value() == 0):
            LCD.fill_rect(60,50,30,30,LCD.red)
            print("DOWM")
        else :
            LCD.fill_rect(60,50,30,30,LCD.white)
            LCD.rect(60,50,30,30,LCD.red)
            
        if(left.value() == 0):
            LCD.fill_rect(15,0,30,30,LCD.red)
            print("LEFT")
        else :
            LCD.fill_rect(15,0,30,30,LCD.white)
            LCD.rect(15,0,30,30,LCD.red)
        
        if(right.value() == 0):
            LCD.fill_rect(105,0,30,30,LCD.red)
            print("RIGHT")
        else :
            LCD.fill_rect(105,0,30,30,LCD.white)
            LCD.rect(105,0,30,30,LCD.red)
        
        if(ctrl.value() == 0):
            LCD.fill_rect(60,0,30,30,LCD.red)
            print("CTRL")
        else :
            LCD.fill_rect(60,0,30,30,LCD.white)
            LCD.rect(60,0,30,30,LCD.red)
            
        LCD.show(0,120,240,240) #Show bottom half
        LCD.fill(LCD.white)
    time.sleep(1)
    LCD.fill(0xFFFF)





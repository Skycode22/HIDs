import network
from machine import Pin, SPI
import framebuf
import time
import os
import usocket as socket

SSID = "touch_2_die"
PASSWORD = "Shast@098123"

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
if not wlan.isconnected():
    print('Connecting to network...')
    wlan.connect(SSID, PASSWORD)
    while not wlan.isconnected():
        pass
print('Network config:', wlan.ifconfig())

BL = 13
DC = 8
RST = 12
MOSI = 11
SCK = 10
CS = 9

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
        self.buffer = bytearray(self.height * self.width * 2)
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
        self.dc(1)
        self.cs(0)
        self.spi.write(self.buffer)
        self.cs(1)

def start_http_server():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ai = socket.getaddrinfo("0.0.0.0", 80)  # Change this line
    addr = ai[0][-1]

    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(addr)
    s.listen(5)
    print("Server is listening on", addr)

    while True:
        res = s.accept()
        client_s = res[0]
        client_addr = res[1]
        print("Client address:", client_addr)
        print("Client socket:", client_s)

        req = client_s.recv(4096)
        print("Request:")
        print(req)

        response = '''HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n
       <html>
<head>
    <title>HomeScreen</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: 'Courier New', monospace;
            background-color: #f0f0f0;
        }
        h1 {
            font-family: 'Times New Roman', serif;
            color: #000c0c;
        }
        .section {
            border: 5px solid #008080;
            padding: 20px;
            margin: 20px;
        }
    </style>
</head>
<body>
    <div id="homescreen" class="section">
        <h1>Welcome to HomeScreen</h1>
        <p>Explore different sites from here:</p>
        <ul>
            <li><a href="https://www.google.com" target="_blank">Google</a></li>
            <li><a href="https://www.openai.com" target="_blank">OpenAI</a></li>
            <li><a href="http:/10.0.0.32" target="_blank">10.0.0.32</a></li>
        </ul>
    </div>
    
    <div id="personal" class="section">
        <h1>Personal</h1>
    </div>
    
    <div id="work" class="section">
        <h1>Work</h1>
        <button onclick="window.open('https://drive.google.com/drive/folders/18dKSjmV_ytnj2O6cc8XOfFppWOwRwLST?usp=drive_linkd', '_blank')">Open Google Drive Folder</button>
    </div>
</body>
</html>
        '''
        client_s.send(response)
        client_s.close()

if __name__=='__main__':
    LCD = LCD_1inch3()

    LCD.fill(LCD.white)
    
    # Obtain the IP address
    ip_address = wlan.ifconfig()[0]
    
    # Display the IP address
    LCD.text("IP Address: {}".format(ip_address), 0, 0, LCD.red)
    
    LCD.show(0,0,240,120)
    LCD.show(0,120,240,240)

    start_http_server()  # start the HTTP server

    time.sleep(1)
    LCD.fill(0xFFFF)


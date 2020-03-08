import ASUS.GPIO as GPIO
import spidev
import time
import threading
import sys
import serial
import os
from smbus2 import SMBus

#GPIO PIN
encoder_sw = 17    #PIN 7
encoder_a  = 166   #PIN 13
encoder_b  = 164   #PIN 11
rotary_counter = 0      # Start counting from 0
current_A = 1           # Assume that rotary switch is not 
current_B = 1           # moving while we init software
lockRotary = threading.Lock()
buttonStatus = 0
start_time = 0
end_time = 0

rotary_mode=0
relayCounter = 0
inputCounter = 0
filter_counter = 0
xfeed_counter = 0
Mute = 0

spi_inuse = 0
ch = 0
zero_point = 0x8000
alarmH_h = 0x80
alarmH_l = 0x80
alarmH = (alarmH_h<<8) + (alarmH_l)
alarmL_h = 0x7F
alarmL_l = 0x80
alarmL = (alarmL_h<<8) + (alarmL_l)
mv=0.01953

5
usb_mode_sw = 167   #PIN 15
i2s_sw      = 224   #PIN 37
I2S_select =1

ac_sw     = 165   #PIN 27
dynalo_sw = 168   #PIN 29

relay_en = 162  #PIN16
relay_s0 = 234  #PIN28
relay_s1 = 171  #PIN22
relay_s2 = 163  #PIN18



#SPI_SDO PIN 19
#SPI_SDI PIN 21
#SPI_CLK PIN 23

pga_enable = 1  #1 to enable PGA2311 volume 0 to dam1941 volume
pga_volume = 0
dam1941_volume = -90


#I2C setting
_I2C = SMBus(1)
_I2C.write_word_data(0x49,0x01,0x8b85)
_I2C.close


#Serial Setting
_LCD_rate = 115200
_LCD_port = '/dev/ttyS1'
_LCD = serial.Serial(_LCD_port, _LCD_rate)

_DAM_rate = 115200
_DAM_port = '/dev/ttyS2'
_DAM = serial.Serial(_DAM_port, _DAM_rate)

def GpioSetup(): 
    GPIO.setwarnings(False)                     #disable warning
    GPIO.setmode(GPIO.ASUS)                     #USE ASUS mode

    GPIO.setup(encoder_sw , GPIO.IN ,pull_up_down=GPIO.PUD_DOWN)            #encoder's switch input and disable pull up resistor
    GPIO.setup(encoder_a , GPIO.IN)             #define encoder channel A and B
    GPIO.setup(encoder_b , GPIO.IN)

    GPIO.add_event_detect(encoder_a, GPIO.RISING, callback = RotaryInterrupt)
    GPIO.add_event_detect(encoder_b, GPIO.RISING, callback = RotaryInterrupt)
    GPIO.add_event_detect(encoder_sw, GPIO.RISING, callback=SwitchInterrupt, bouncetime=250)

    GPIO.setup(usb_mode_sw , GPIO.OUT)
    GPIO.setup(i2s_sw , GPIO.OUT)
    GPIO.setup(ac_sw , GPIO.OUT)
    GPIO.setup(dynalo_sw , GPIO.OUT)
    GPIO.setup(relay_en , GPIO.OUT)
    GPIO.setup(relay_s0 , GPIO.OUT)
    GPIO.setup(relay_s1 , GPIO.OUT)
    GPIO.setup(relay_s2 , GPIO.OUT)


def GpioInit():
    GPIO.output(usb_mode_sw,GPIO.LOW)
    GPIO.output(i2s_sw,GPIO.LOW)
    GPIO.output(ac_sw,GPIO.LOW)
    GPIO.output(dynalo_sw,GPIO.LOW)
    GPIO.output(relay_en,GPIO.LOW)
    GPIO.output(relay_s0,GPIO.LOW)
    GPIO.output(relay_s1,GPIO.LOW)
    GPIO.output(relay_s2,GPIO.LOW)




def XlrOn():
        print("XLR is ON!!")
        GPIO.output(relay_s0,GPIO.LOW)
        GPIO.output(relay_s1,GPIO.LOW)
        GPIO.output(relay_s2,GPIO.LOW)

def PentaconOn():
        print("4.4 is ON!!")
        GPIO.output(relay_s0,GPIO.HIGH)
        GPIO.output(relay_s1,GPIO.LOW)
        GPIO.output(relay_s2,GPIO.LOW)

def Jack25On():
        print("2.5 is ON!!")
        GPIO.output(relay_s0,GPIO.LOW)
        GPIO.output(relay_s1,GPIO.HIGH)
        GPIO.output(relay_s2,GPIO.LOW)

def Jack63On():
        print("6.3 is ON!!")
        GPIO.output(relay_s0,GPIO.HIGH)
        GPIO.output(relay_s1,GPIO.HIGH)
        GPIO.output(relay_s2,GPIO.LOW)

def LineXlrOn():
        print("LINE OUT XLR is ON!!")
        GPIO.output(relay_s0,GPIO.LOW)
        GPIO.output(relay_s1,GPIO.LOW)
        GPIO.output(relay_s2,GPIO.HIGH)

def LineRcaOn():
        print("LINE OUT RCA is ON!!")
        GPIO.output(relay_s0,GPIO.HIGH)
        GPIO.output(relay_s1,GPIO.LOW)
        GPIO.output(relay_s2,GPIO.HIGH)

def XMOSON():
    print("I2S input set to XMOS")
    GPIO.output(i2s_sw,GPIO.HIGH)

def VolumioOn():
    print("I2S input set to Volumio")
    GPIO.output(i2s_sw,GPIO.LOW)

def UsbModeSwitch():
    GPIO.output(usb_mode_sw,GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(usb_mode_sw,GPIO.LOW)


def DigitalInput_Auto():
    _DAM.write(b"I7\r\n")

def DigitalInput_USB():
    _DAM.write(b"I0\r\n")

def DigitalInput_AES():
    _DAM.write(b"I1\r\n")

def DigitalInput_BNC():
    _DAM.write(b"I2\r\n")

def DigitalInput_RCA():
    _DAM.write(b"I3\r\n")

def DigitalInput_TOS():
    _DAM.write(b"I4\r\n")

def DigitalInput_I2S():
    _DAM.write(b"I5\r\n")

def AcPowerOn():
    GPIO.output(ac_sw,GPIO.HIGH)

def AudioOutputOn():
    GPIO.output(relay_en,GPIO.HIGH)

def AudioOutputMute():
    GPIO.output(relay_en,GPIO.LOW)

def AudioOutputSwitch(s):
    AudioOutputMute()
    

def DamListener():
    while True:
        while _DAM.in_waiting:
            data_raw = _DAM.readline()
            data = data_raw.decode()
            print('raw data ', data_raw)
            print('decoded data ', data)
            LCDTx(data)

def LCDInit():
    packet = bytearray([0xFF,0X55,0x0,0x0,0x1,0x1])#open LCD
    _LCD.write(packet)
    packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x0])#feq INIT
    _LCD.write(packet)
    packet = bytearray([0xFF,0X55,0x0,0x2,0x1,0])#init volume
    _LCD.write(packet)

    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x1])#Auto Init
    _LCD.write(packet)

    packet = bytearray([0xFF,0X55,0x0,0x5,0x1,0x0])
    _LCD.write(packet)

    packet = bytearray([0xFF,0X55,0x0,0x6,0x1,0x0])
    _LCD.write(packet)
    packet = bytearray([0xFF,0X55,0x0,0x4,0x1,0x1])
    _LCD.write(packet)

def LCDTx(data):
    global I2S_select
    if(data=='L044\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x1])
        _LCD.write(packet)
    elif(data=='L048\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x2])
        _LCD.write(packet)
    elif(data=='L088\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x3])
        _LCD.write(packet)
    elif(data=='L096\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x4])
        _LCD.write(packet)
    elif(data=='L176\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x5])
        _LCD.write(packet)
    elif(data=='L192\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x6])
        _LCD.write(packet)
    elif(data=='L352\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x7])
        _LCD.write(packet)
    elif(data=='L384\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x8])
        _LCD.write(packet)
    elif(data=='L02M\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x9])
        _LCD.write(packet)
    elif(data=='L05M\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x10])
        _LCD.write(packet)
    elif(data=='L11M\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x11])
        _LCD.write(packet)
    elif(data=='L000\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x1,0x1,0x0])
        _LCD.write(packet)


    elif(data=='I7\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x7])
        packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x1])
        _LCD.write(packet)
    elif(data=='I0\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x0])
        _LCD.write(packet)
    elif(data=='I1\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x1])
        _LCD.write(packet)
    elif(data=='I2\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x2])
        _LCD.write(packet)
    elif(data=='I3\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x3])
        _LCD.write(packet)
    elif(data=='I4\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x4])
        _LCD.write(packet)
    elif(data=='I5\r\n'):
        if(I2S_select == 0):
            packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x5])
        elif(I2S_select ==1):
            packet = bytearray([0xFF,0X55,0x0,0x3,0x1,0x6])
        _LCD.write(packet)

    elif(data=='F4\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x6,0x1,0x0])
        _LCD.write(packet)
    elif(data=='F5\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x6,0x1,0x1])
        _LCD.write(packet)
    elif(data=='F6\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x6,0x1,0x2])
        _LCD.write(packet)
    elif(data=='F7\r\n'):
        packet = bytearray([0xFF,0X55,0x0,0x6,0x1,0x3])
        _LCD.write(packet)
    
def LCDListener():
    while True:
        while _LCD.in_waiting:
            data_raw = _LCD.readline()
            data = data_raw.decode()
            print('raw data ', data_raw)
            print('decoded data ', data)



def VolumioControl():
    global rotary_counter, lockRotary ,relayCounter,rotary_mode,inputCounter,I2S_select
    global filter_counter, xfeed_counter
    volume=0
    while True:
        time.sleep(0.1)

        lockRotary.acquire()
        newCounter = rotary_counter
        rotary_counter = 0
        lockRotary.release()
        
        if(newCounter != 0):
            if(rotary_mode==0):
                print('volume control mode')
                if pga_enable:
                    volume = volume + newCounter*1
                    if volume < 0:
                        volume = 0
                    if volume > 255:
                        volume = 255
                else:
                    volume = volume + newCounter
                    if volume < -90:
                        volume = -90
                    if volume > 10:
                        volume = 10
                db=31.5-(0.5*(255-volume))
                print(db)
                PgaSetVolume(volume)
                packet = bytearray([0xFF,0X55,0x0,0x2,0x1,volume])
                _LCD.write(packet)
            
            elif(rotary_mode ==1):
                print('Output control mode')
                relayCounter += newCounter
                if relayCounter >5:
                    relayCounter =0
                if relayCounter < 0:
                    relayCounter =5

                if relayCounter==0:
                    XlrOn()
                elif relayCounter==1:
                    PentaconOn()
                elif relayCounter==2:
                    Jack25On()
                elif relayCounter==3:
                    Jack63On()
                elif relayCounter==4:
                    LineXlrOn()
                elif relayCounter==5:
                    LineRcaOn()
                packet = bytearray([0xFF,0X55,0x0,0x4,0x1,relayCounter+1])
                _LCD.write(packet)

            elif(rotary_mode ==2):
                #input select
                print('input control mode')
                inputCounter += newCounter
                if(inputCounter>7):
                    inputCounter = 0
                if(inputCounter < 0):
                    inputCounter = 7

                if(inputCounter==0):
                    DigitalInput_Auto()                
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x1])
                    _LCD.write(packet)
                elif(inputCounter==1):
                    DigitalInput_USB()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==2):
                    DigitalInput_AES()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==3):
                    DigitalInput_BNC()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==4):
                    DigitalInput_RCA()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==5):
                    DigitalInput_TOS()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==6):
                    I2S_select = 0
                    XMOSON()
                    DigitalInput_I2S()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)
                elif(inputCounter==7):
                    I2S_select = 1
                    VolumioOn()
                    DigitalInput_I2S()
                    packet = bytearray([0xFF,0X55,0x0,0x8,0x1,0x0])
                    _LCD.write(packet)


            elif(rotary_mode ==3):
                #filter select
                print('filter control mode')
                filter_counter += newCounter
                if(filter_counter>3):
                    filter_counter = 0
                if(filter_counter < 0):
                    filter_counter = 3
                
                if(filter_counter==0):
                    _DAM.write(b"F4\r\n")
                elif(filter_counter==1):
                    _DAM.write(b"F5\r\n")
                elif(filter_counter==2):
                    _DAM.write(b"F6\r\n")
                elif(filter_counter==3):
                    _DAM.write(b"F7\r\n")

            elif(rotary_mode ==4):
                #crossfeed xelect
                print('crossfeed control mode')
                
                xfeed_counter += newCounter
                if(xfeed_counter>3):
                    xfeed_counter = 0
                if(xfeed_counter < 0):
                    xfeed_counter = 3

                if(xfeed_counter==0):
                    _DAM.write(b"X0\r\n")
                    packet = bytearray([0xFF,0X55,0x0,0x5,0x1,0x0])
                    _LCD.write(packet)
                elif(xfeed_counter==1):
                    _DAM.write(b"X1\r\n")
                    packet = bytearray([0xFF,0X55,0x0,0x5,0x1,0x1])
                    _LCD.write(packet)
                elif(xfeed_counter==2):
                    _DAM.write(b"X2\r\n")
                    packet = bytearray([0xFF,0X55,0x0,0x5,0x1,0x2])
                    _LCD.write(packet)
                elif(xfeed_counter==3):
                    _DAM.write(b"X3\r\n")
                    packet = bytearray([0xFF,0X55,0x0,0x5,0x1,0x3])
                    _LCD.write(packet)
            
def RotaryInterrupt(A_or_B):
    global rotary_counter, current_A, current_B, lockRotary
    switch_A = GPIO.input(encoder_a)
    switch_B = GPIO.input(encoder_b)

    if current_A == switch_A and current_B == switch_B:
        return
    
    current_A = switch_A
    current_B = switch_B

    if(switch_A and switch_B):
        lockRotary.acquire()
        if A_or_B == encoder_b:
            rotary_counter = 1
        else:
            rotary_counter = -1
        lockRotary.release()
    return

def SwitchInterrupt(switch):
                                                            #rotary will make a noise at the end 
                                                            #SO it have to make a timer for bouncing
    global buttonStatus,start_time,end_time,rotary_mode
    if start_time == 0 :
        start_time = time.time()
        while 1:
            if GPIO.input(switch) == 0:
                end_time = time.time()
                break
    else:
        start_time == 0
        return

    buttonTime = end_time - start_time

    if 2>buttonTime>0.01:                                     #for wrong interrupt
        rotary_mode+=1
        if(rotary_mode>4):
            rotary_mode = 0
        packet = bytearray([0xFF,0X55,0x0,0x7,0x1,rotary_mode])
        _LCD.write(packet)
    elif buttonTime>=5:
        AudioOutputMute()
        packet = bytearray([0xFF,0X55,0x0,0x0,0x1,0x0])#LCD OFF
        _LCD.write(packet)
        print('power off!!')
        os.system("shutdown now -h")



    else:
        start_time = 0
        return

    start_time = 0

def PgaSetVolume(volume):
    global spi_inuse
    spi_inuse = 1
    spi = spidev.SpiDev()
    spi.open (2,0)
    spi.max_speed_hz = 500000
    spi.mode = 0b00
    data = [volume,volume,volume,volume]
    spi.xfer2(data)
    spi.close
    spi_inuse = 0

def AdcInit():
    global spi_inuse
    if (spi_inuse ==0):
        spi_inuse = 1
        spi = spidev.SpiDev ()
        spi.open (2,1 )
        spi.max_speed_hz = 17000000 #17MHz
        spi.bits_per_word = 8
        spi.mode = 0b01

        data = [0x85,0x00,0x00,0x00] #reset the device
        spi.xfer2(data)

        data = [0x07,0x13,0x00] #feature setting    
        spi.xfer2(data)

        data = [0x0B,0x0B,0x00] #Ch0 input range setting
        spi.xfer2(data)
        data = [0x0D,0x0B,0x00] #Ch1 input range setting
        spi.xfer2(data)
        data = [0x0F,0x0B,0x00] #Ch2 input range setting
        spi.xfer2(data)
        data = [0x11,0x0B,0x00] #Ch3 input range setting
        spi.xfer2(data)

        #High Alarm Setting
        data = [0x2D,alarmH_h,0x00] #Ch0 High alarm setting high bit
        spi.xfer2(data)
        data = [0x2F,alarmH_l,0x00] #Ch0 High alarm setting low bit
        spi.xfer2(data)
        data = [0x37,alarmH_h,0x00] #Ch1 High alarm setting high bit
        spi.xfer2(data)
        data = [0x39,alarmH_l,0x00] #Ch1 High alarm setting low bit
        spi.xfer2(data)
        data = [0x41,alarmH_h,0x00] #Ch2 High alarm setting high bit
        spi.xfer2(data)
        data = [0x43,alarmH_l,0x00] #Ch2 High alarm setting low bit
        spi.xfer2(data)
        data = [0x4B,alarmH_h,0x00] #Ch3 High alarm setting high bit
        spi.xfer2(data)
        data = [0x4D,alarmH_l,0x00] #Ch3 High alarm setting low bit
        spi.xfer2(data)

        #Low Alarm Setting

        #High Alarm Setting
        data = [0x31,alarmL_h,0x00] #Ch0 High alarm setting high bit
        spi.xfer2(data)
        data = [0x33,alarmL_l,0x00] #Ch0 High alarm setting low bit
        spi.xfer2(data)
        data = [0x3B,alarmL_h,0x00] #Ch1 High alarm setting high bit
        spi.xfer2(data)
        data = [0x3D,alarmL_l,0x00] #Ch1 High alarm setting low bit
        spi.xfer2(data)
        data = [0x45,alarmL_h,0x00] #Ch2 High alarm setting high bit
        spi.xfer2(data)
        data = [0x47,alarmL_l,0x00] #Ch2 High alarm setting low bit
        spi.xfer2(data)
        data = [0x4F,alarmL_h,0x00] #Ch3 High alarm setting high bit
        spi.xfer2(data)
        data = [0x51,alarmL_l,0x00] #Ch3 High alarm setting low bit
        spi.xfer2(data)

        spi.close
        spi_inuse = 0
    else:
        return


def DcVoltageMonitor():
    global spi_inuse,ch
    if (spi_inuse ==0):
        spi_inuse = 1
        spi = spidev.SpiDev ()
        spi.open (2,1 )
        spi.max_speed_hz = 17000000 #17MHz
        spi.bits_per_word = 8
        spi.mode = 0b01


        while 1:
            if(ch == 0):
                data = [0xC0,0x00,0x00,0x00,0x00]
            elif(ch == 1):
                data = [0xC4,0x00,0x00,0x00,0x00]
            elif(ch == 2):
                data = [0xC8,0x00,0x00,0x00,0x00]
            elif(ch == 3):
                data = [0xCC,0x00,0x00,0x00,0x00]
            else:
                ch = 0
                data = [0xC0,0x00,0x00,0x00,0x00]
            spi.xfer2(data)
            data = [0x00,0x00,0x00,0x00,0x00,0x00]
            adc_data=spi.xfer2(data)
            packet = bytearray([0xFF,0X55,0x0,0x9+ch,0x2,adc_data[2],adc_data[3]])
            _LCD.write(packet)

            data = [0x12<<1,0x00,0x00]
            alarm_active=spi.xfer2(data)
                                                 #debug output
            print('alarm actived:',alarm_active)
            

            if(alarm_active[2]==0):
                data = [0x11<<1,0x00,0x00]
                alarm_tripped=spi.xfer2(data)
                
                print('alarm tripped:',alarm_tripped)
                print('Alarm release')
                print('SDO: ',adc_data)
                decoded_data = (adc_data[2]<<8)+(adc_data[3])
                print('decode data: ',decoded_data)
                point_data=decoded_data-zero_point
                print('point data:',point_data)
                mv_data=point_data*mv
                print('dc mv: ',mv_data)
                print('high alarm :',alarmH)
                print('low alarm :',alarmL)
                
            else:
                
                print('WARNING!!! DC VOLTAGE OVER PROTECT!!!!')
                print('SDO: ',adc_data)
                decoded_data = (adc_data[2]<<8)+(adc_data[3])
                print('decode data: ',decoded_data)
                point_data=decoded_data-zero_point
                print('point data:',point_data)
                mv_data=point_data*mv
                print('dc mv: ',mv_data)
                print('high alarm :',alarmH)
                print('low alarm :',alarmL)
                

            ch += 1
            time.sleep(1)
        spi.close
        spi_inuse = 0
    else:
        return

def main():
    
    GpioSetup()
    GpioInit()
    AcPowerOn()
    time.sleep(1)
    AudioOutputOn()
    AdcInit()
    LCDInit()
    PgaSetVolume(0)

    _DAM_Listener = threading.Thread(target = DamListener)
    _DAM_Listener.start()

    VolumioControler = threading.Thread(target = VolumioControl)
    VolumioControler.start()

    _ADC_Listener = threading.Thread(target= DcVoltageMonitor)
    _ADC_Listener.start()
    while(1):
        GPIO.output(usb_mode_sw,GPIO.HIGH)
        time.sleep(0.1)
        GPIO.output(usb_mode_sw,GPIO.LOW)
        time.sleep(2)

main()




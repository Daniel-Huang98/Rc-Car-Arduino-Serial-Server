import serial
import time

#serial interface example
#written by Daniel Huang 

def SendSpeed(speed): #servo and motor interface
    byteH = speed | 255;
    byteL = (speed >> 8) | 255
    checksum = (70+36+steering+speed)%256 #calc 8bit checksum 
    ser.write((('F${}{}{}').format(chr(byteL),chr(byteH),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port
    
#max steering range is 115 to 60


ser = serial.Serial('/dev/ttyUSB0') #open serial port 

steering = 115 #sample values 
speed = 0
steering = 60
flag = 1
while(True): #makes servo move back and forth and motor start and stop indefinitely 
    if(speed == 1000):
        flag = 0
    elif(speed == 0):
        flag = 1
    if(flag == 0):
        speed+=-1
    elif(flag == 1):
        speed+=1
    print ("speed: ", speed)
    SendSpeed(speed)

ser.close() #close serial port

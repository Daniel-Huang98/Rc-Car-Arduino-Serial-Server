import serial
import time

#serial interface example
#written by Daniel Huang 

def SendSpeed(speed): #servo and motor interface
    byteL = speed & 0xFF
    byteH = (speed >> 8) & 0xFF
    print (byteH,byteL)
    checksum = (70+36+byteL+byteH)%256 #calc 8bit checksum 
    ser.write((('F${}{}{}').format(chr(byteH),chr(byteL),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port
    


ser = serial.Serial('/dev/ttyUSB0') #open serial port 

steering = 115 #sample values 
speed = 25500
steering = 60
flag = 1

while(True): #makes servo move back and forth and motor start and stop indefinitely 
    if(speed >= 40500):
        flag = 0
    elif(speed <= 25500):
        flag = 1
    if(flag == 0):
        speed+=-10
    elif(flag == 1):
        speed+=10
    print ("speed: ", speed)
    SendSpeed(speed)

ser.close() #close serial port

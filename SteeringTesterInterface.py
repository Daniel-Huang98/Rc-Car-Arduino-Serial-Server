import serial
import time

#serial interface example
#written by Daniel Huang 

def SendVal(val,ser): #servo and motor interface
    byteL = val & 0xFF
    byteH = (val >> 8) & 0xFF
    print (byteH,byteL)
    checksum = (70+36+byteL+byteH)%256 #calc 8bit checksum 
    ser.write((('F${}{}{}').format(chr(byteH),chr(byteL),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port
    

steeringSer = serial.Serial('/dev/ttyUSB1') #open serial port 

steering = 90 #sample values 
flag = 1

while(True): #makes servo move back and forth and motor start and stop indefinitely 
    if(steering >= 115):
        flag = 0
    elif(steering <= 60):
        flag = 1
    if(flag == 0):
        steering+=-1
    elif(flag == 1):
        steering+=1
    print ("speed: ", steering)
    SendVal(steering,steeringSer)

steeringSer.close() #close serial port

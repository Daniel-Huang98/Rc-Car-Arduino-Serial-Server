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
speedSer = serial.Serial('/dev/ttyUSB0') #open serial port 

steering = 90 #sample values 
flagSteering = 1
flagSpeed = 1
speed = 25500
while(True): #makes servo move back and forth and motor start and stop indefinitely 

    #steering
    if(steering >= 115):
        flagSteering = 0
    elif(steering <= 60):
        flagSteering = 1
    if(flagSteering == 0):
        steering+=-1
    elif(flagSteering == 1):
        steering+=1
    #endsteering
    #Speed
    if(speed >= 27000):
        flagSpeed = 0
    elif(speed <= 25500):
        flagSpeed = 1
    if(flagSpeed == 0):
        speed+=-1
    elif(flagSpeed == 1):
        speed+=1
    #endSpeed
    SendVal(steering,steeringSer)
    SendVal(speed,speedSer)


steeringSer.close() #close serial port
speedSer.close() #close serial port

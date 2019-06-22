import serial
import time


def SendVal(val,ser): #servo and motor interface
    byteL = val & 0xFF
    byteH = (val >> 8) & 0xFF
    print (byteH,byteL)
    checksum = (70+36+byteL+byteH)%256 #calc 8bit checksum 
    ser.write((('F${}{}{}').format(chr(byteH),chr(byteL),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port


out = ""
flag = 0
while(True):
    try:
        ser = serial.Serial('/dev/ttyUSB1') #open serial port 
        break
    except:
        print("waiting to connect")
ser.flushInput()
while(ser.inWaiting()<= 0):
    SendVal(4739,ser)
while(ser.inWaiting()>0):
    inVal = ser.read(1)
    if(chr(inVal[0]) == '$'):
        break
    out += str(chr(inVal[0]))
print("connected to", out)

    

    

ser.close() #close serial port
    

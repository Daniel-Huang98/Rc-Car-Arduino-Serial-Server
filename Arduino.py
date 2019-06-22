import serial
import time

#/dev/ttyUSB1

class ArduinoHandler:
    def __init__(self,serialIn):
        self.serialIn = serialIn
    

    def SendVal(self,val): #servo and motor interface
        byteL = val & 0xFF
        byteH = (val >> 8) & 0xFF
        checksum = (70+36+byteL+byteH)%256 #calc 8bit checksum 
        self.ser.write((('F${}{}{}').format(chr(byteH),chr(byteL),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port
    
    def Test(self):
        pass
    
    def connectNonSecure(self):
        print("connecting to device")
        while(True):
            try:
                self.ser = serial.Serial(self.serialIn) #open serial port 
                print("connected")
                break
            except:
                pass


    def connect(self):
        out = ""
        flag = 0
        print("connecting to device")
        while(True):
            try:
                self.ser = serial.Serial(self.serialIn) #open serial port 
                break
            except:
                pass
        self.ser.flushInput()
        while(self.ser.inWaiting()<= 0):
            self.SendVal(255)
            time.sleep(1)
        while(self.ser.inWaiting()>0):
            inVal = self.ser.read(1)
            if(chr(inVal[0]) == '$'):
                break
            out += str(chr(inVal[0]))
        print("connected to", out)
    
    def close(self):
        self.ser.close()


class Steering(ArduinoHandler):
    def Test(self):
        print("running steering test")
        flagSteering = 0
        steering = 90
        while(True):
            #steering
            print(steering)
            if(steering >= 115):
                flagSteering = 0
            elif(steering <= 60):
                flagSteering = 1
            if(flagSteering == 0):
                steering+=-1
            elif(flagSteering == 1):
                steering+=1
            #endsteering
            self.SendVal(steering)
    

class Throttle(ArduinoHandler):
    def Test(self):
        flagSpeed = 1
        speed = 26000
        while(True):
            if(speed >= 26500):
                flagSpeed = 0
            elif(speed <= 26000):
                flagSpeed = 1
            if(flagSpeed == 0):
                speed+=-1
            elif(flagSpeed == 1):
                speed+=1
            self.SendVal(speed)
    
    

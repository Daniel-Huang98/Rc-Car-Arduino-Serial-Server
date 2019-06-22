class ArduinoHandler:
    def __init__(self,ser):
        self.ser = ser
    

    def SendVal(self,val): #servo and motor interface
        byteL = val & 0xFF
        byteH = (val >> 8) & 0xFF
        checksum = (70+36+byteL+byteH)%256 #calc 8bit checksum 
        self.ser.write((('F${}{}{}').format(chr(byteH),chr(byteL),chr(checksum))).encode('utf-8')) #format into ascii string and then write to port
    
    def Test(self):
        pass
    
    def connect(self):
        pass


class Steering(ArduinoHandler):
    def Test(self):
        flagSteering = 1
        while(True):
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
            self.SendVal(steering)
    def connect(self):
        pass

class Throttle(ArduinoHandler):
    def Test(self):
        flagSpeed = 1
        while(True):
            if(speed >= 27000):
                flagSpeed = 0
            elif(speed <= 25500):
                flagSpeed = 1
            if(flagSpeed == 0):
                speed+=-1
            elif(flagSpeed == 1):
                speed+=1
            self.SendVal(steering)
    
    def connect(self):
        pass

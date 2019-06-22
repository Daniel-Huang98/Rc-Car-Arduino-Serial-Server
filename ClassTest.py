from Arduino import ArduinoHandler, Steering, Throttle




Speed = Throttle("/dev/ttyUSB1")
Speed.connect()
Speed.Test()
Speed.close()

Steer = Steering("/dev/ttyUSB1")
Steer.connect()
Steer.Test()
Steer.close()
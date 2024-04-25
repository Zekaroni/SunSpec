import RPi.GPIO as GPIO
import time

class Motor:
    def __init__(self, pin: int, ):
        self.pin = pin
        self.servo = GPIO.PWM(servoPIN, 50)
        self.servo.start(0)

    def changeDutyCycle(self, posistion: int):
        pass


servoPIN = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setup(servoPIN, GPIO.OUT)
p = GPIO.PWM(servoPIN, 50)
p.start(2.5)
seat = list(range(20)) + list(range(20, 1, -1))
try:
  while True:
    for i in seat:
        p.ChangeDutyCycle(i)
        time.sleep(0.1)
except KeyboardInterrupt:
  p.stop()
  GPIO.cleanup()
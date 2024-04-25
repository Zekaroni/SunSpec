from picamera2 import Picamera2
from time import time


picam2 = Picamera2()
config = picam2.create_still_configuration()
picam2.configure(config)

picam2.start()
start = time()

index = 500
while True:
    picam2.capture_file(f"./test/{index}.jpg")
    print("captured image", index)
    index+=1



picam2.stop()

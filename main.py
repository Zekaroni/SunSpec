from lib.spectrometer    import USB2000P
from lib.cameraHandler   import Camera
from lib.imageProcessing import ImageHandler
from lib.motorDriver     import Motor

from time import time

def mainLoop():
    # Init all components
    spectrometer   = USB2000P()
    camera         = Camera()
    imageProcessor = ImageHandler()
    baseMotor      = Motor()
    cameraMotor    = Motor()
    
    while True:
        timestamp = time()

        # Take image and run it through processing
        imagePath = f"./output/full/{timestamp}.jpg"
        camera.takePicture(imagePath)
        while True:
            try:
                image = open(imagePath)
                processedImage = imageProcessor(image)
            except OSError:
                pass
        



if __name__ == "__main__":
    mainLoop()
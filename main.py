from lib.spectrometer    import USB2000P
from lib.cameraHandler   import Camera
from lib.imageProcessing import ImageHandler
from lib.motorDriver     import Motor

import matplotlib.pyplot as plt

from time import time

def mainLoop():
    # Init all components
    spectrometer   = USB2000P()
    camera         = Camera()
    baseMotor      = Motor()
    cameraMotor    = Motor()

    for i in range(1):
        timestamp = time()
        image = camera.takePicture(timestamp)
        if image:
            processedImage = ImageHandler(image)
            processedImage.resize([640,360])
            max_index = processedImage.getMaxHeatMapIndex()
            plt.imshow(processedImage._heatmap, cmap='hot', interpolation='nearest')
            plt.colorbar()
            plt.text(max_index[1], max_index[0], f"Max", color='black', fontsize=8, ha='center')
            plt.savefig(f"./output/heatmaps/{timestamp}.jpg")
            plt.clf()
        else:
            print(camera.exception)
            # TODO: Log error
            pass
    
    camera.shutdown()

        



if __name__ == "__main__":
    mainLoop()
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from time import time

class ImageHandler:
    def __init__(self, image):
        self.image = image
    
    def resize(self, size):
        self.image.thumbnail(size, Image.NEAREST)
    
    def getPixelMaxs(self):
        pixels = np.array(self.image)
        maxs = np.amax(pixels, axis=2)
        return maxs
    
    def getHeatMapArray(self):
        data = self.getPixelMaxs()

        section_width = data.shape[1] // 16
        section_height = data.shape[0] // 9

        averages = []
        for i in range(9):
            for j in range(16):
                section = data[i * section_height:(i + 1) * section_height, j * section_width:(j + 1) * section_width]
                average = np.mean(section)
                averages.append(average)

        return np.array(averages).reshape(9, 16)


if __name__ == "__main__":
    start = time()
    img = ImageHandler(Image.open("test.jpg"))
    img.resize([640,360])

    heatmap_data = img.getHeatMapArray()
    
    max_index = np.unravel_index(np.argmax(heatmap_data), heatmap_data.shape)

    print(f"Took {time() - start} seconds\n{heatmap_data}\n{max_index}")

    hottest_section = f"Max"

    plt.imshow(heatmap_data, cmap='hot', interpolation='nearest')
    plt.colorbar()
    
    plt.text(max_index[1], max_index[0], hottest_section, color='black', fontsize=12, ha='center')
    
    plt.show()

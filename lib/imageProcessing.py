from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import colorsys

from time import time

class ImageHandler:
    def __init__(self, image: Image) -> None:
        """
        Used for processing images of the Sunspec project.

        Parameters
            image: PIL.Image.Image
        """
        self.image = image
        self._heatmap = None
        self._max_heatmap_index = None
    
    def resize(self, size: list[int]) -> None:
        """
        Resizes the image stored in self.image using the PIL.Image.NEAREST method
        This method was chosen because of it's speed:accuracy

        Parameters
            size: list[int] = [int,int]
        """
        self.image.thumbnail(size, Image.NEAREST)
    
    def getPixelsBrightness(self) -> np.ndarray:
        """
        Returns the brightest value of each pixel in the image.

        Returns:
            np.ndarray: Brightness values of each pixel.
        """
        grayscale_image = self.image.convert('L')
        pixel_data = np.array(grayscale_image.getdata())
        print(pixel_data)
        return pixel_data
    
    def getHeatMapArray(self, size: list[int] = [160,90]) -> np.ndarray:
        """
        Calculates a heat map of MAX brightness values from the image

        Parameters
            size: list[int] = [int,int] ==> [16,9]
        
        Return
            np.ndarray
        """
        data = self.getPixelsBrightness()
        heatmap = data.reshape(self.image.size[1], self.image.size[0])

        # Determine the size of each block
        block_height = heatmap.shape[0] // size[1]
        block_width = heatmap.shape[1] // size[0]

        # Resize the heatmap
        heatmap_resized = np.zeros((size[1], size[0]))  # Swap the dimensions
        for i in range(size[1]):  # Iterate over rows (which corresponds to the height)
            for j in range(size[0]):  # Iterate over columns (which corresponds to the width)
                start_x = block_height * i
                start_y = block_width * j
                end_x = start_x + block_height
                end_y = start_y + block_width
                # Take the maximum brightness value within the block
                heatmap_resized[i][j] = np.max(heatmap[start_x:end_x, start_y:end_y])

        self._heatmap = heatmap_resized
        return heatmap_resized

    def getMaxHeatMapIndex(self) -> list[int, int]:
        if self._heatmap == None:
            self.getHeatMapArray()
        max_index: tuple = np.unravel_index(np.argmax(self._heatmap), self._heatmap.shape)
        self._max_heatmap_index = max_index
        return max_index


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 0:
        start: float = time()
        try:
            image: Image.Image = Image.open(sys.argv[1])
        except Exception:
            raise FileNotFoundError("The argument provided was invalid")
        img = ImageHandler(image)
        img.resize([640,360])
        img.image.save("processed.jpg")
        heatmap_data: np.ndarray = img.getHeatMapArray()
        max_index = img.getMaxHeatMapIndex(heatmap_data)

        print(f"Took {time() - start} seconds")
        if "-g" in sys.argv:
            plt.imshow(heatmap_data, cmap='gray', interpolation='nearest')
            plt.colorbar()
            plt.text(max_index[1], max_index[0], f"Max", color='black', fontsize=8, ha='center')
            plt.show()
    else:
        raise ValueError("No argument provided for file path")
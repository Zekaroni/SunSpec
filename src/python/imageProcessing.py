from PIL import Image
import time

class ImageHandler:
    def __init__(self, image: Image):
        self.image: Image = image
    
    def resize(self, size: list) -> None:
        self.image.thumbnail(size, Image.Resampling.LANCZOS)
    
    def getPixelAverages(self) -> list:
        pixels = self.image.load()
        width, height = self.image.size
        averages = []
        for y in range(height):
            averages.append([])
            for x in range(width):
                averages[y].append(round(sum(pixels[x,y])/3))
        return averages

if __name__ == "__main__":
    img = ImageHandler(Image.open("test.jpg"))
    # start = time.time()
    # a = img.getPixelAverages()
    # print(f"Took {time.time() - start} seconds with full res")

    start = time.time()
    img.resize([160,90])
    b = img.getPixelAverages()
    print(f"Took {time.time() - start} seconds with 640x480")

    a = img.getPixelAverages()
    
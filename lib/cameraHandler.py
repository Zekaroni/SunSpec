from picamera2 import Picamera2
from PIL import Image

class Camera:
    def __init__(self):
        self.picam2 = Picamera2()
        self.config = self.picam2.create_still_configuration()
        self.picam2.configure(self.config)
        self.picam2.start()
        self.output_path = "./output/images"
        self.exception = None

    def takePicture(self, filename: str) -> bool:
        try:
            __path = f"{self.output_path}/{filename}.jpg"
            self.picam2.capture_file(__path)
            return Image.open(__path)
        except Exception as e:
            self.exception = e
            return False
    
    def shutdown(self) -> None:
        self.picam2.stop()
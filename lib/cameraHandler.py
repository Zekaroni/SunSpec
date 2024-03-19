from picamera2 import Picamera2

class Camera:
    def __init__(self):
        self.picam2 = Picamera2()
        self.config = self.picam2.create_still_configuration()
        self.picam2.configure(self.config)
        self.picam2.start()

    def takePicture(self, file_path: str) -> None:
        self.picam2.capture_file(file_path)
    
    def shutdown(self) -> None:
        self.picam2.stop()
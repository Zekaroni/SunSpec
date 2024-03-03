import time
import picamera

def take_picture(file_path):
    with picamera.PiCamera() as camera:
        camera.resolution = (1024, 768)
        time.sleep(2)
        camera.capture(file_path)
        print(f"Picture taken and saved as {file_path}")

if __name__ == "__main__":
    file_name = "captured_image.jpg" 
    take_picture(file_name)

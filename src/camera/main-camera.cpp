#include <iostream>
#include <raspicam/raspicam.h>

int main(int argc, char **argv) {
    raspicam::RaspiCam Camera;

    if (!Camera.open()) {
        std::cerr << "Error opening the camera" << std::endl;
        return -1;
    }

    // Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    // Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    uint8_t *data = new uint8_t[Camera.getImageTypeSize()];

    Camera.grab();
    Camera.retrieve(data, raspicam::RASPICAM_FORMAT_IGNORE);

    std::ofstream outFile("example.jpg", std::ios::binary);
    outFile.write(reinterpret_cast<char*>(data), Camera.getImageTypeSize());
    outFile.close();

    delete[] data;
    Camera.release();

    return 0;
}
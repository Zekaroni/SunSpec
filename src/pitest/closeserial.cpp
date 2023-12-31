#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi." << std::endl;
        return 1;
    }

    const char* device = "/dev/serial0";
    
    int serialPort = serialOpen(device, 9600);
    if (serialPort == -1) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }
    serialClose(serialPort);
    std::cout << "Serial was closed" << std::endl;
    return 0;
}
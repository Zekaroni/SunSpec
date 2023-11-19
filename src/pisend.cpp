#include <wiringPi.h>
#include <serial.h>
#include <iostream>

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi." << std::endl;
        return 1;
    }

    const char* device = "/dev/ttyS0";

    int serialPort = serialOpen(device, 9600);
    if (serialPort == -1) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }
    
    const char* sendData = "Hello, RS232!";
    serialPrintf(serialPort, "%s\n", sendData);
    while (serialDataAvail(serialPort) > 0) {
        char receivedChar = serialGetchar(serialPort);
        std::cout << receivedChar;
    }

    serialClose(serialPort);
    return 0;
}

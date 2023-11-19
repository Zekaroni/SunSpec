#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

int main() {
    const char* device = "/dev/serial0";
    
    int serialPort = serialOpen(device, 9600);
    if (serialPort == -1) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    } else
    {
        std::cout << "It worked" << std::endl;
    };

    while (true) {
        while (serialDataAvail(serialPort) > 0) {
            char receivedChar = serialGetchar(serialPort);
            std::cout << receivedChar;
        }
        delay(100);
    }

    serialClose(serialPort);

    return 0;
}

#include <iostream>

int main() {
    const char* device = "/dev/serial0";

    int serialPort = serialOpen(device, 9600);
    if (serialPort == -1)
    {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    } else
    {
        std::cout << "Opened serial." << std::endl;
    };
    
    std::string input;
    while (1) {
        std::cout << "Enter a string: ";
        std::getline(std::cin, input);
        serialPrintf(serialPort, "%s\n", input.c_str());
    }

    serialClose(serialPort);
    return 0;
}

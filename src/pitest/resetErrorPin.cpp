#include <wiringPi.h>
#include <iostream>

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi." << std::endl;
        return 1;
    }
    pinMode(22, OUTPUT);
    digitalWrite(22, LOW);
    return 0;
}

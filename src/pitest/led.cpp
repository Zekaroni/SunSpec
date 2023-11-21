#include <wiringPi.h>
#include <iostream>

#define LED_PIN_1 0
#define LED_PIN_2 1

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi." << std::endl;
        return 1;
    }
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    digitalWrite(LED_PIN_1, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_2, LOW);
    return 0;
}

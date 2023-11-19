#pragma once
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>


class SerialCommunication
{
    public:
        int serialPort = serialOpen(device, 9600);
        const char* device = "/dev/serial0";
        
        void SendData(uint16_t data)
        {
            serialPrintf(serialPort, "%s\n", data);
        };

        void Close()
        {
            serialClose(serialPort);
        };
       
        

    SerialCommunication()
    {
        if (wiringPiSetup() == -1) {
            std::cout << "Failed to initialize WiringPi." << std::endl;
        }
        if (serialPort == -1) {
            std::cerr << "Failed to open serial port." << std::endl;
        }
    };
};

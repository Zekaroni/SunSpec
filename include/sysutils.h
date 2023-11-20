#pragma once
#include <fstream>
#include <thread>
#include <chrono>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "RS232Commands.h"
#include "logging.h"

namespace UTILS
{
    std::ofstream RX_RESPONSE_OUT("./shared/rx", std::ios::out | std::ios::trunc);
    std::ifstream RX_RESPONSE_IN("./shared/rx", std::ios::binary);
    std::ofstream TX_RESPONSE_OUT("./shared/tx", std::ios::out | std::ios::trunc);
    std::ifstream TX_RESPONSE_IN("./shared/tx", std::ios::binary);

    char RX_READ()
    {
        char response;
        RX_RESPONSE_IN.get(response);
        if (response)
        {
            LogCall("Success");
            return response;
        } else
        {
            LogError("Rx Failed To Be Read");
        };
    };

    void RX_WRITE(char value)
    {
        LogCall("Success");
        RX_RESPONSE_OUT << value;
    };

    char TX_READ()
    {
        char response;
        TX_RESPONSE_IN.get(response);
        if (response)
        {
            LogCall("Success");
            return response;
        } else
        {
            LogError("Tx Failed To Be Read");
        };
    };

    void TX_WRITE(char value)
    {
        LogCall("Success");
        TX_RESPONSE_OUT << value;
    };

    void microSleep(uint16_t microseconds)
    {
        LogCall(std::to_string(microseconds));
        std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
    };

    void miliSleep(uint16_t milliseconds)
    {
        LogCall(std::to_string(milliseconds));
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    };

    void sleep(uint16_t seconds)
    {
        LogCall(std::to_string(seconds));
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    };

    class SerialCommunication
    {
        public:
            int serialPort = serialOpen(device, 9600);
            const char* device = "/dev/serial0";

            void QueueCommand(char command)
            {
                LogCall(std::to_string(command));
                serialPrintf(serialPort, "%c", command);
            };
            
            void QueueData(uint16_t data)
            {
                LogCall(std::to_string(data));
                serialPrintf(serialPort, "%u", data);
            };

            void SendData()
            {
                // NOTE: The data must be queued first before sending a CR
                serialPrintf(serialPort, "%s", ResponseCodes::CR);
            };

            void Close()
            {
                serialClose(serialPort);
            };        

        SerialCommunication()
        {
            if (wiringPiSetup() == -1) {
                LogError("Failed to initialize WiringPi.")
            };
            if (serialPort == -1) {
                LogError("Failed to open serial port.") 
            };
        };
    };
};

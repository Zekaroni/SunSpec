#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "RS232Commands.h"

const std::string FILENAME = "ERROR_LOG.brctc";
std::ofstream LOG(FILENAME, std::ios::app);
std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::stringstream ss;
    ss << milliseconds;
    return ss.str();
}
#define LogError(values){LOG << getTimestamp() << " | " << __func__ << " | " << values << std::endl;}

void SendData16(char command, uint16_t data)
{
    std::cout << command << data << std::endl;
};

void SendData32(char command, uint32_t data)
{
    std::cout << command << data << std::endl;
};

void SendVariableRequest(uint8_t data)
{
    std::cout << RS232::QUERY_PARAM_VALUES << data << std::endl;
};

void SendDataStandalone16(uint16_t data)
{
    std::cout << data << std::endl;
};

void SendRegisterUpdate(uint16_t address, uint16_t value)
{
    std::cout << RS232::SET_REGISTER_VALUE << address << value << std::endl;
};

void SendDataModeUpdate(char command, char followChar)
{
    std::cout << command << followChar << std::endl;
};

void RS232Commands::AddScans(uint16_t scans)
{
    if (scans < 5001 && scans > 0)
    {
        SendData16(RS232::ADD_SCANS, scans);
    } else
    {
        LogError(std::to_string(scans));
    };
};

void RS232Commands::SetPixelBoxcarWidth(uint16_t width)
{
    if (width < 16 && width >= 0)
    {
        SendData16(RS232::SET_PIXEL_BOXCAR, width);
    } else
    {
        LogError(std::to_string(width))
    };
};

void RS232Commands::SetDataCompression(bool state)
{
    if (state)
    {
        SendData16(RS232::SET_DATA_COMPRESSION, static_cast<uint16_t>(1));
    } else
    {
        SendData16(RS232::SET_DATA_COMPRESSION, 0);
    };
};

void RS232Commands::IntegrationTime16Bit(int16_t miliseconds)
{
    if (miliseconds < 65001 && miliseconds > 0)
    {
        SendData16(RS232::SET_INTEGRATION_TIME_16, miliseconds);
    } else
    {
        LogError(std::to_string(miliseconds));
    };
};

void RS232Commands::IntegrationTime32Bit(int32_t microseconds)
{
    if (microseconds > 999 && microseconds < 65000001)
    {
        SendData32(RS232::SET_INTEGRATION_TIME_32, microseconds);
    } else
    {
        LogError(std::to_string(microseconds));
    };
};

void RS232Commands::SetLampState(bool state)
{
    SendData16(RS232::SET_LAMP_LINE, static_cast<uint16_t>(state));
};

void RS232Commands::SetBaudRate(uint16_t value)
{
    if (value >= 0 && value < 7)
    {
        SendData16(RS232::SET_BAUD_RATE, value);
    } else
    {
        LogError(std::to_string(value));
    };
};

void RS232Commands::ClearMemory()
{
    SendData16(RS232::CLEAR_MEMORY, static_cast<uint16_t>(1));
};

void RS232Commands::SetDataStorageMode(bool value)
{
    SendData16(RS232::SET_DATA_STORAGE_MODE, static_cast<uint16_t>(value));
};

void RS232Commands::SetPixelMode(uint8_t value, uint16_t param1, uint16_t param2, uint16_t param3)
{
    if (value >= 0 && value < 5)
    {
        switch (value)
        {
            case 0:
                SendData16(RS232::SET_PIXEL_MODE, value);
                break;
                
            case 1:
                if (param1 > 0 && param1 < 1024)
                {
                    SendData16(RS232::SET_PIXEL_MODE, value);
                    SendDataStandalone16(static_cast<uint16_t>(param1));
                } else
                {
                    LogError("Parameter 1 not valid : " + std::to_string(static_cast<short>(param1)));
                };
                break;
            case 2:
                LogError("Case 2 stated N/A (test)")
                break;
            case 3:
                if (param1 > 0 && param2 > 0 && param3 > 0 && param1 < 1024 && param2 < 1024 && param3 < 1024)
                {
                    SendData16(RS232::SET_PIXEL_MODE, value);
                    SendDataStandalone16(param1);
                    SendDataStandalone16(param2);
                    SendDataStandalone16(param3);
                } else
                {
                    LogError("Invalid parameter for case 3")
                };
                break;
            case 4:
                LogError("Case 4 is not supported in this API")
                break;
        };
    } else
    {
        LogError(std::to_string(value));
    };
};

void RS232Commands::GetSpectralData()
{
    SendDataStandalone16(RS232::GET_SPECTRAL_DATA);
};

void RS232Commands::SetTriggerMode(uint16_t value)
{
    if (value >= 0 && value < 4)
    {
        SendData16(RS232::SET_TRIGGER_MODE, value);
    } else
    {
        LogError("Invalid value : " + std::to_string(value));
    };
};

void RS232Commands::SetRegisterValue(uint16_t address, uint16_t value)
{
    SendRegisterUpdate(address, value);
};

void RS232Commands::SetASCIIMode()
{
    // PLEASE DO NOT SWITCH TO THIS MODE UNLESS YOU HAVE PROPERLY HANDLED IT
    SendDataModeUpdate(RS232::SET_ASCII_MODE, 'A');
};

void RS232Commands::SetBINMode()
{
    SendDataModeUpdate(RS232::SET_BIN_MODE, 'B');
};

void RS232Commands::SetChecksumMode(bool state)
{
    SendData16(RS232::SET_CHECKSUM_MODE, static_cast<uint16_t>(state));
};

void RS232Commands::GetVersionNumber()
{
    SendDataStandalone16(RS232::GET_VERSION_NUMBER);
};

void RS232Commands::GetVariableInformation(char command)
{
    bool validData = false;
    const uint8_t VALID_COUNT = 7;
    char validCommands[VALID_COUNT] = {'A','B','I','K','T','J','y'};
    for (uint8_t i = 0; i < VALID_COUNT; i++)
    {
        if (validCommands[i] == command)
        {
            SendVariableRequest(command);
            validData = true;
            break;
        };
    };
    if (!validData)
    {
        std::string strCommand[1];
        strCommand[0] = command;
        LogError("Invalid char passed : " + strCommand[0]);
    };
};

int main()
{
    RS232Commands spectrometer;
    // spectrometer.AddScans(50);
    // spectrometer.SetPixelBoxcarWidth(13);
    // spectrometer.SetDataCompression(1);
    // spectrometer.IntegrationTime16Bit(32000);
    // spectrometer.IntegrationTime32Bit(4333291);
    // spectrometer.SetLampState(false);
    // spectrometer.SetBaudRate(9);
    // spectrometer.ClearMemory();
    // std::cout << ResponseCodes::ACK << std::endl;
    // spectrometer.SetDataStorageMode(1);
    // spectrometer.SetPixelMode(3,53,22,84);
    // spectrometer.SetBaudRate(BaudRates::BAUD_115200);
    // spectrometer.SetRegisterValue(0xFE, 0x00);
    // spectrometer.SetTriggerMode(2);
    // spectrometer.SetASCIIMode();
    // spectrometer.SetBINMode();
    spectrometer.GetVariableInformation('c');
};
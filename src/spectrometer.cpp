#include <iostream>
#include "../include/RS232Commands.h"
#include "../include/logging.h"
#include "../include/sysutils.h"

SerialCommunication serialCommunicator;

void SendData16(char command, uint16_t data)
{
    LogCall(std::to_string(command) + ", " + std::to_string(data));
    serialCommunicator.QueueCommand(command);
    serialCommunicator.QueueData16(data);
    serialCommunicator.SendData();
};

void SendData32(char command, uint32_t data)
{
    LogCall(std::to_string(command) + ", " + std::to_string(data));
    serialCommunicator.QueueCommand(command);
    serialCommunicator.QueueData32(data);
    serialCommunicator.SendData();
};

void SendVariableRequest(char data)
{
    LogCall(std::to_string(data));
    serialCommunicator.QueueCommand(RS232::QUERY_PARAM_VALUES);
    serialCommunicator.QueueChar(data);
    serialCommunicator.SendData();
};

void SendDataStandalone16(uint16_t data)
{
    LogCall(std::to_string(data));
    serialCommunicator.QueueData16(data);
    serialCommunicator.SendData();
};

void SendRegisterUpdate(uint16_t address, uint16_t value)
{
    LogCall(std::to_string(address) + ", " + std::to_string(value));
    serialCommunicator.QueueData16(address);
    serialCommunicator.QueueData16(value);
    serialCommunicator.SendData();
};

void SendDataModeUpdate(char command, char followChar)
{
    LogCall(std::to_string(command) + ", " + std::to_string(followChar));
    serialCommunicator.QueueCommand(command);
    serialCommunicator.QueueChar(followChar);
    serialCommunicator.SendData();
};

void RS232Commands::AddScans(uint16_t scans)
{
    if (scans < 5001 && scans > 0)
    {
        LogCall(std::to_string(scans));
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
        LogCall(std::to_string(width));
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
    LogCall(std::to_string(state));
};

void RS232Commands::IntegrationTime16Bit(int16_t miliseconds)
{
    if (miliseconds < 65001 && miliseconds > 0)
    {
        LogCall(std::to_string(miliseconds));
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
        LogCall(std::to_string(microseconds));
        SendData32(RS232::SET_INTEGRATION_TIME_32, microseconds);
    } else
    {
        LogError(std::to_string(microseconds));
    };
};

void RS232Commands::SetLampState(bool state)
{
    LogCall(std::to_string(state))
    SendData16(RS232::SET_LAMP_LINE, static_cast<uint16_t>(state));
};

void RS232Commands::SetBaudRate(uint16_t value)
{
    if (value >= 0 && value < 7)
    {
        LogCall(std::to_string(value));
        SendData16(RS232::SET_BAUD_RATE, value);
    } else
    {
        LogError(std::to_string(value));
    };
};

void RS232Commands::ClearMemory()
{
    LogCall("1");
    SendData16(RS232::CLEAR_MEMORY, static_cast<uint16_t>(1));
};

void RS232Commands::SetDataStorageMode(bool value)
{
    LogCall(std::to_string(value));
    SendData16(RS232::SET_DATA_STORAGE_MODE, static_cast<uint16_t>(value));
};

void RS232Commands::SetPixelMode(uint8_t value, uint16_t param1, uint16_t param2, uint16_t param3)
{
    if (value >= 0 && value < 5)
    {
        switch (value)
        {
            case 0:
                LogCall(std::to_string(value));
                SendData16(RS232::SET_PIXEL_MODE, value);
                break;
                
            case 1:
                if (param1 > 0 && param1 < 1024)
                {
                    LogCall(std::to_string(value) + ", " + std::to_string(param1));
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
                    LogCall(std::to_string(value) + ", " + std::to_string(param1) + ", " + std::to_string(param2) + ", " + std::to_string(param3));
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
    LogCall("1");
    SendDataStandalone16(RS232::GET_SPECTRAL_DATA);
};

void RS232Commands::SetTriggerMode(uint16_t value)
{
    if (value >= 0 && value < 4)
    {
        LogCall(std::to_string(value));
        SendData16(RS232::SET_TRIGGER_MODE, value);
    } else
    {
        LogError("Invalid value : " + std::to_string(value));
    };
};

void RS232Commands::SetRegisterValue(uint16_t address, uint16_t value)
{
    // NOTE: EXCERSIZE CAUTION USING THIS COMMAND
    LogCall(std::to_string(address) + ", " + std::to_string(value));
    SendRegisterUpdate(address, value);
};

void RS232Commands::SetASCIIMode()
{
    // NOTE: PLEASE DO NOT SWITCH TO THIS MODE UNLESS YOU HAVE PROPERLY HANDLED IT
    LogCall("A");
    SendDataModeUpdate(RS232::SET_ASCII_MODE, 'A');
};

void RS232Commands::SetBINMode()
{
    LogCall("B");
    SendDataModeUpdate(RS232::SET_BIN_MODE, 'B');
};

void RS232Commands::SetChecksumMode(bool state)
{
    LogCall(std::to_string(state));
    SendData16(RS232::SET_CHECKSUM_MODE, static_cast<uint16_t>(state));
};

void RS232Commands::GetVersionNumber()
{
    LogCall("1");
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
            LogCall(std::to_string(command));
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
    LOGGING::runChecks();
    RS232Commands spectrometer;
    UTILS::awaitResponse(spectrometer, &RS232Commands::AddScans, static_cast<uint16_t>(3990));
    std::cout << "Finished waiting" << std::endl;
    // spectrometer.AddScans(50);
    // spectrometer.SetPixelBoxcarWidth(13);
    // spectrometer.SetDataCompression(1);
    // spectrometer.IntegrationTime16Bit(32000);
    // spectrometer.IntegrationTime32Bit(4333291);
    // spectrometer.SetLampState(false);
    // spectrometer.SetBaudRate(BaudRates::BAUD_115200);
    // spectrometer.ClearMemory();
    // // std::cout << ResponseCodes::ACK << std::endl;
    // spectrometer.SetDataStorageMode(1);
    // spectrometer.SetPixelMode(3,53,22,84);
    // spectrometer.SetBaudRate(BaudRates::BAUD_9600);
    // spectrometer.SetRegisterValue(0xFE, 0x00);
    // spectrometer.SetTriggerMode(2);
    // spectrometer.SetASCIIMode();
    // spectrometer.SetBINMode();
    // spectrometer.GetVariableInformation('A');
};
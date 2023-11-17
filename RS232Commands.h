#include <cstdint>

namespace RS232
{
    // Page 29
    const char ADD_SCANS               = 'A';
    const char SET_PIXEL_BOXCAR        = 'B';
    const char SET_DATA_COMPRESSION    = 'G';
    const char SET_INTEGRATION_TIME_16 = 'I';
    const char SET_INTEGRATION_TIME_32 = 'i';
    const char SET_LAMP_LINE           = 'J';
    const char SET_BAUD_RATE           = 'K';
    const char CLEAR_MEMORY            = 'L';
    const char SET_DATA_STORAGE_MODE   = 'M';
    const char SET_PIXEL_MODE          = 'P';
    const char GET_SPECTRAL_DATA       = 'S';
    const char SET_TRIGGER_MODE        = 'T';
    const char SET_REGISTER_VALUE      = 'W';
    const char READ_SCANS_FROM_MEM     = 'Z';
    const char SET_ASCII_MODE          = 'a';
    const char SET_BIN_MODE            = 'b';
    const char SET_CHECKSUM_MODE       = 'k';
    const char OXYGEN                  = 'o';
    const char GET_TEMPERATURE         = 't';
    const char SET_OXYGEN_CALIBRATION  = 'u';
    const char GET_VERSION_NUMBER      = 'v';
    const char SET_CALIBRATION_COEF    = 'x';
    const char SET_16_BIT_TIMER_OP     = 'y';
    const char QUERY_PARAM_VALUES      = '?';
    const char READ_PLUG_IN_DEVS       = '+';
    const char USB2000_IDENTIFIER      = '_';
};

namespace BaudRates
{
    // Page 32
    const uint16_t BAUD_2400          = 0;
    const uint16_t BAUD_4800          = 1;
    const uint16_t BAUD_9600          = 2; // Default of spectrometer
    const uint16_t BAUD_19200         = 3;
    const uint16_t BAUD_38400         = 4;
    const uint16_t BAUD_NOT_SUPPORTED = 5;
    const uint16_t BAUD_115200        = 6;
};

namespace ResponseCodes
{
    const char ACK = 0x06;
    const char ENTER = 0x0D;
    const char NAK = 0x15;
};


namespace USBCommands
{
    const uint8_t Initialize                        = 0x01;
    const uint8_t SetIntegrationTime                = 0x02;
    const uint8_t SetStrobeEnableStatus             = 0x03;
    const uint8_t SetShutdownMode                   = 0x04;
    const uint8_t QueryInformation                  = 0x05;
    const uint8_t WriteInformation                  = 0x06;
    const uint8_t RequestSpectra                    = 0x09;
    const uint8_t SetTriggerMode                    = 0x0A;
    const uint8_t QueryNumberOfAccessories          = 0x0B;
    const uint8_t QueryPluginIdentifiers            = 0x0C;
    const uint8_t DetectPlugins                     = 0x0D;
    const uint8_t GeneralI2CRead                    = 0x60;
    const uint8_t GeneralI2CWrite                   = 0x61;
    const uint8_t GeneralSPIIO                      = 0x62;
    const uint8_t WriteRegisterInformation          = 0x6A;
    const uint8_t ReadRegisterInformation           = 0x6B;
    const uint8_t ReadPCBTemperature                = 0x6C;
    const uint8_t ReadIrradianceCalibrationFactors  = 0x6D;
    const uint8_t WriteIrradianceCalibrationFactors = 0x6E;
    const uint8_t QueryInformationFE                = 0xFE;
};

class RS232Commands
{
    // TODO: Figure out how to disearn ACK from NAK ASCII
    public:
        void AddScans(uint16_t scans);
        void SetPixelBoxcarWidth(uint16_t width);
        void SetDataCompression(bool state);
        void IntegrationTime16Bit(int16_t miliseconds);
        void IntegrationTime32Bit(int32_t microseconds);
        void SetLampState(bool state);
        void SetBaudRate(uint16_t value); // Use AvailableBaudRate namespace, refernce page 32
        void ClearMemory();               // No paramaters are needed since 0 or 1 clears data
        void SetDataStorageMode(bool value);
        void SetPixelMode(uint8_t value, uint16_t param1 = -1, uint16_t param2 = -1, uint16_t param3 = -1); // NOTE: Does NOT support value 4 from page 33
        void GetSpectralData();
        void SetTriggerMode(uint16_t value);
        void SetRegisterValue(uint16_t address, uint16_t value); // THE MOTHERLOAD
        void SetASCIIMode(); // Please for the love of god don't use this
        void SetBINMode();
        void SetChecksumMode(bool state);
        void GetVersionNumber();
        void GetVariableInformation(char command); // Uses RS232Commands namespace
};
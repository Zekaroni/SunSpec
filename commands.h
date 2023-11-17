#include <cstdint>

struct Commands
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


struct QueryInformationOuput
{
    // Page 17-18
    uint8_t InitializationByte; // Should be 0x05
    uint8_t ConfigurationIndex; // See page 18 in DataSheet
    uint8_t ASCII0;
    uint8_t ASCII1;
    uint8_t ASCII2;
    uint8_t ASCII3;
    uint8_t ASCII4;
    uint8_t ASCII5;
    uint8_t ASCII6;
    uint8_t ASCII7;
    uint8_t ASCII8;
    uint8_t ASCII9;
    uint8_t ASCII10;
    uint8_t ASCII11;
    uint8_t ASCII12;
    uint8_t ASCII13;
    uint8_t ASCII14;
};

struct QueryInformationFE
{
    struct SubPixelCount
    {
        uint8_t PixelByte2;
        uint8_t PixelByte1;
    };
    union PixelCountUnion
    {
        SubPixelCount PixelBytes;
        uint16_t PixelCount;
    };
    PixelCountUnion PixelCount;
    uint32_t ItegrationTime; 
    uint8_t LampEnable; // Bool LOW, HIGH
    uint8_t TriggerModeValue;
    uint8_t SpectralAcuisitionValue;

};
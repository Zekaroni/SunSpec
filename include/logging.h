#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <wiringPi.h>


namespace LOGGING
{
    const int ERROR_PIN = 22;
    std::ofstream ERROR_LOG("./log/ERROR.log", std::ios::app);
    std::ofstream CALL_LOG("./log/CALL.log", std::ios::app);
    std::ofstream RESPONSE_LOG("./log/RESPONSE.log", std::ios::app);

    std::string getTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::stringstream ss;
        ss << milliseconds;
        return ss.str();
    };
    
    void runChecks()
    {
        if (wiringPiSetup() == -1)
        {
            std::cerr << "Failed to initialize WiringPi." << std::endl;
            throw std::runtime_error("WiringPi initialization failed.");
        };
        pinMode(ERROR_PIN, OUTPUT);
        if (!ERROR_LOG.is_open())  
        {
        throw std::runtime_error("ERROR_LOG failed to open.");
        }
        else if (!CALL_LOG.is_open())
        {
        throw std::runtime_error("CALL_LOG failed to open.");
        } 
        else if (!RESPONSE_LOG.is_open())
        {
        throw std::runtime_error("RESPONSE_LOG failed to open.");
        };
    };
};



// NOTE: All log values must be std::string. Use std::to_string() to convert different data types.
#define LogError(values){LOGGING::ERROR_LOG << LOGGING::getTimestamp() << " | " << __FILE__ << " | " << __func__ << " | " << values << std::endl;digitalWrite(LOGGING::ERROR_PIN, HIGH);}
#define LogCall(values){LOGGING::CALL_LOG << LOGGING::getTimestamp() << " | " << __FILE__ << " | " << __func__ << " | " << values << std::endl;}
#define LogResponse(values){LOGGING::RESPONSE_LOG << LOGGING::getTimestamp() << " | " << values << std::endl;}

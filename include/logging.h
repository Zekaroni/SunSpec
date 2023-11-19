#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


namespace LOGGING
{
    std::ofstream ERROR_LOG("./log/ERROR.log", std::ios::app);
    std::ofstream CALL_LOG("./log/CALL.log", std::ios::app);
    std::ofstream RECIEVE_LOG("./log/RECIEVE.log", std::ios::app);

    std::string getTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::stringstream ss;
        ss << milliseconds;
        return ss.str();
    };
};

// NOTE: All log values must be std::string. Use std::to_string() to convert different data types.
#define LogError(values){LOGGING::ERROR_LOG << LOGGING::getTimestamp() << " | " << __FILE__ << " | " << __func__ << " | " << values << std::endl;}
#define LogCall(values){LOGGING::CALL_LOG << LOGGING::getTimestamp() << " | " << __FILE__ << " | " << __func__ << " | " << values << std::endl;}
#define LogRecieve(values){LOGGING::RECIEVE_LOG << LOGGING::getTimestamp() << " | " << values << std::endl;}

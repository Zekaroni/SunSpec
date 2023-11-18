#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::ofstream ERROR_LOG("../log/ERROR.log", std::ios::app);
std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::stringstream ss;
    ss << milliseconds;
    return ss.str();
}
#define LogError(values){ERROR_LOG << getTimestamp() << " | " << __FILE__ << " | " << __func__ << " | " << values << std::endl;}

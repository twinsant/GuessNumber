#pragma once

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

inline std::string getFormatTime(){
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto output_time = std::localtime(&time_t_now);
    std::ostringstream oss;
    oss << std::put_time(output_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
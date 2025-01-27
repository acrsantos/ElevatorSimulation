#include "logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>

Logger::Logger() {
    // Create or open the file in append mode.
    std::ofstream outf {"activity_log.txt", std::ios::app};
}
Logger::~Logger() {
    outf.close();
}

void Logger::log(std::string_view level, std::string_view msg) {

    // Get the current time
    std::chrono::time_point t = std::chrono::system_clock::now();

    // Convert to time_t to be able to format
    time_t time = std::chrono::system_clock::to_time_t(t);

    // Output the time in the format: [YYYY-MM-DD HH:MM:SS], the log level, and the message
    outf << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] " << level << ": " << msg << '\n';
}


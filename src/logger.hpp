#pragma once

#include <iostream>
#include <fstream>

class Logger {
public:
    Logger();
    ~Logger();
    static void log(std::string_view level, std::string_view msg);
private:
    inline static std::ofstream outf {"activity_log.txt", std::ios::app};
};

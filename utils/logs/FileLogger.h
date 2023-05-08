#pragma once 

#include "ILogger.h"
#include <fstream>

class FileLogger : public ILogger {
public:
    FileLogger(const std::string &filename);
    std::ostream& stream();
    ~FileLogger();

private:
    std::ofstream file;
};
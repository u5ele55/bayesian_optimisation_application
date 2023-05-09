#pragma once

#include "AbstractLogger.h"
#include <fstream>

class FileLogger : public AbstractLogger {
public:
    explicit FileLogger(const std::string &filename);

    std::ostream &stream() override;

    ~FileLogger() override;

private:
    std::ofstream file;
};
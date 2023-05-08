#pragma once

#include <ostream>
#include <vector>

class ILogger {
public:
    virtual std::ostream& stream() = 0;
    virtual ~ILogger() {};
};

void printSystem(std::ostream &output, const std::vector<double>& values);
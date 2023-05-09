#pragma once

#include <ostream>
#include <vector>

class AbstractLogger {
public:
    virtual std::ostream& stream() = 0;

    void printSystem(const std::vector<double>& values);

    virtual ~AbstractLogger() = default;
};

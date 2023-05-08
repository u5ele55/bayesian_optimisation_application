#include "ILogger.h"

void printSystem(std::ostream &output, const std::vector<double>& values) {
    output << values.size() << "\n";
    for (auto it : values) {
        output << it << "\n";
    }
}
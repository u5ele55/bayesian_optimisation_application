#include "AbstractLogger.h"

void AbstractLogger::printSystem(const std::vector<double> &values) {
    stream() << values.size() << "\n";
    for (auto it : values) {
        stream() << it << "\n";
    }
}

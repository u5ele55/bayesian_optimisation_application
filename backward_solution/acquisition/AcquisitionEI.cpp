#include "AcquisitionEI.h"

#include <cmath>

double AcquisitionEI::operator()(double yBest, double mean, double std)
{
    double z = ((std == 0) ? 0 : (yBest - mean) / std);
    auto cdf = [](double x) {
        return std::erfc(-x / std::sqrt(2)) / 2;
    };
    auto pdf = [](double x) {
        return exp(-x*x / 2) * M_2_SQRTPI * M_SQRT1_2 / 2;
    };
    return -((yBest  - mean + 0.05) * cdf(z) + std * pdf(z));
}

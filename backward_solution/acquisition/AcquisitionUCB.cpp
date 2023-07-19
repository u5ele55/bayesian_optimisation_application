#include <iostream>
#include "AcquisitionUCB.h"

AcquisitionUCB::AcquisitionUCB(double deviationCoef)
    : deviationCoef(deviationCoef)
{
}

double AcquisitionUCB::operator()(double yBest, double mean, double std)
{
    return mean - std * deviationCoef;
}

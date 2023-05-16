#include "AcquisitionUCB.h"

AcquisitionUCB::AcquisitionUCB(double deviationCoef)
    : deviationCoef(deviationCoef)
{
}

double AcquisitionUCB::operator()(double yBest, const Vector &mean, const Vector &std)
{
    
}

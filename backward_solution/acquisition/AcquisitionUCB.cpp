#include "AcquisitionUCB.h"

AcquisitionUCB::AcquisitionUCB(double deviationCoef)
    : deviationCoef(deviationCoef)
{
}

double AcquisitionUCB::operator()(const VectorXd &x, VectorXd &grad)
{
    // ? 
}

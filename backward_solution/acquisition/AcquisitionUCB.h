#pragma once 

#include "IAcquisition.h"

class AcquisitionUCB : public IAcquisition {
public:
    AcquisitionUCB( double deviationCoef );
    double operator()(double yBest, const Vector &mean, const Vector &std);
private:
    double deviationCoef;
};
#pragma once 

#include "IAcquisition.h"

class AcquisitionUCB : public IAcquisition {
public:
    AcquisitionUCB( double deviationCoef );
    double operator()(double yBest, double mean, double std);
private:
    double deviationCoef;
};
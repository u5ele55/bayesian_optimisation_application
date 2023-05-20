#pragma once 

#include "IAcquisition.h"

class AcquisitionEI : public IAcquisition {
public:
    double operator()(double yBest, double mean, double std);
};
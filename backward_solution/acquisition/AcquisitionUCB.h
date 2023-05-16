#pragma once 

#include "IAcquisition.h"

class AcquisitionUCB : public IAcquisition {
public:
    AcquisitionUCB( double deviationCoef );
    double operator()(const VectorXd& x, VectorXd& grad);
private:
    double deviationCoef;
};
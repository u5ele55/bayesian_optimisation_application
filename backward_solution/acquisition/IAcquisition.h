#pragma once

#include <Eigen/Core>
#include <LBFGS.h>

#include "../../utils/Vector.h"

using Eigen::VectorXd;

class IAcquisition {
public:
    virtual double operator()(double yBest, double mean, double std) = 0; 
};
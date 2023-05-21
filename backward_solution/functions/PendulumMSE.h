//
// Created by ormequ on 04.05.23.
//

#pragma once

#include "AbstractForwardSolver.h"
#include "IFunction.h"
#include <vector>

class PendulumMSE : public IFunction {
public:
    PendulumMSE(AbstractForwardSolver &solver, double stddev, double step = 0.1);

    double operator()(const Vector &v, bool cache = true) const;

    std::vector<double> getTrueValues();

    double getStep() const;
private:
    size_t pointsQuantity;
    double stddev;
    double step;
    std::vector<double> trueValues;
};

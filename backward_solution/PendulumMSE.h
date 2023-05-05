//
// Created by ormequ on 04.05.23.
//

#pragma once

#include "../forward_problem/AbstractForwardSolver.h"

#include <vector>

class PendulumMSE {
public:
    PendulumMSE(AbstractForwardSolver &solver, double step = 0.1);

    double operator()(const Vector &v, bool cache = true) const;

private:
    size_t pointsQuantity;
    double step;
    std::vector<double> trueValues;
};

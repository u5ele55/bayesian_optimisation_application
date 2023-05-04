//
// Created by ormequ on 04.05.23.
//

#pragma once
#include "../forward_problem/AbstractForwardSolver.h"

class PendulumMSE {
public:
    PendulumMSE(AbstractForwardSolver &solver, size_t pointsQuantity, double step = 0.1);

    double operator() (const Vector &v) const;
private:
    AbstractForwardSolver &solver;
    size_t pointsQuantity;
    double step;
};

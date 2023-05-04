//
// Created by ormequ on 04.05.23.
//

#include "PendulumMSE.h"
#include "../forward_problem/RK4Solver.h"
#include <cmath>

PendulumMSE::PendulumMSE(AbstractForwardSolver &solver, size_t pointsQuantity, double step)
        : pointsQuantity(pointsQuantity), step(step), trueValues(pointsQuantity) {
    for (int i = 0; i < pointsQuantity; i++) {
        trueValues[i] = solver.getState(step * i)[0];
    }
}

double PendulumMSE::operator()(const Vector &v) const {
    double res = 0;

    auto compareSystem = System(v[0], v[1], v[2], v[3]);
    auto compSolver = RK4ForwardSolver(compareSystem);

    for (int i = 0; i < pointsQuantity; i++) {
        double compareValue = compSolver.getState(step * i)[0];
        res += (trueValues[i] - compareValue) * (trueValues[i] - compareValue);
    }
    res /= static_cast<double>(pointsQuantity);
    res = sqrt(res);

    return res;
}

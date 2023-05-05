//
// Created by ormequ on 04.05.23.
//

#include "PendulumMSE.h"
#include "../forward_problem/RK4Solver.h"
#include <cmath>
#include <iostream>

#define MAX_POINT_QUANTITY 1000
#define MIN_POINT_QUANTITY 10
#define EPS 0.05

PendulumMSE::PendulumMSE(AbstractForwardSolver &solver, double step)
        : step(step),
          pointsQuantity(0) {
    
    for (int i = 0; i < MAX_POINT_QUANTITY; i++) {
        double value = solver.getState(step * i)[0];
        if (i > MIN_POINT_QUANTITY && fabs(value) < EPS) {
            double derivative = (value - trueValues[pointsQuantity-1]) / step;
            if (fabs(derivative) < EPS) {
                std::cout << "Reached " << i * step << " time, breaking here \n";
                std::cout << value << " " << derivative << '\n';
                break;
            }
        }
        pointsQuantity ++;
        trueValues.push_back(value);
    }

    std::cout << "Result pointQuantity in MSE: " << pointsQuantity << '\n';
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

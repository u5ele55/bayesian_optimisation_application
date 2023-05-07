//
// Created by ormequ on 04.05.23.
//

#include "PendulumMSE.h"
#include "../forward_problem/RK4Solver.h"
#include "../utils/SolutionCache.h"
#include <cmath>
#include <iostream>

#define MAX_POINT_QUANTITY 1000
#define MIN_POINT_QUANTITY 10
#define EPS 0.03

PendulumMSE::PendulumMSE(AbstractForwardSolver &solver, double step)
        : step(step),
          pointsQuantity(0) {
    
    for (int i = 0; i < MAX_POINT_QUANTITY; i++) {
        double value = solver.getState(step * i)[0];
        if (i > MIN_POINT_QUANTITY && fabs(value) < EPS) {
            double derivative = (value - trueValues[pointsQuantity-1]) / step;
            if (fabs(derivative) < EPS) {
                std::cout << "Reached " << i * step << " time, breaking here \n";
                break;
            }
        }
        pointsQuantity ++;
        trueValues.push_back(value);
    }
    std::cout << "Result pointQuantity in MSE: " << pointsQuantity << '\n';
    // SolutionCache::getInstance().add(solver.getInitializer(), step, trueValues);
}

double PendulumMSE::operator()(const Vector &v, bool cache) const {
    double res = 0;

    auto compareSystem = System(v[0], v[1], v[2], v[3]);
    auto compSolver = RK4ForwardSolver(compareSystem);

    auto compareValues = SolutionCache::getInstance().get(v);
    bool solve = compareValues.empty() && cache;
    if (solve) {
        compareValues = std::vector<double>(pointsQuantity);
    }

    for (int i = 0; i < pointsQuantity; i++) {
        if (solve) {
            compareValues[i] = compSolver.getState(step * i)[0];
        }
        res += (trueValues[i] - compareValues[i]) * (trueValues[i] - compareValues[i]);
    }
    res /= static_cast<double>(pointsQuantity);
    res = sqrt(res);

    if (cache) {
        SolutionCache::getInstance().add(v, compareValues);
    }
    return res;
}

std::vector<double> PendulumMSE::getTrueValues() {
    return trueValues;
}

double PendulumMSE::getStep() const {
    return step;
}

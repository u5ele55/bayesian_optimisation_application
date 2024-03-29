//
// Created by ormequ on 04.05.23.
//

#include "PendulumMSE.h"
#include "RK4Solver.h"
#include "SolutionCache.h"
#include <cmath>
#include <iostream>

#define MAX_POINT_QUANTITY 1000
#define MIN_POINT_QUANTITY 10
#define POINT_WINDOW 20

PendulumMSE::PendulumMSE(AbstractForwardSolver &solver, double stddev, ISystemFabric *fabric, double step)
        : step(step),
          pointsQuantity(0),
          systemFabric(fabric) {
    int smallValueCounter = 0;
    for (int i = 0; i < MAX_POINT_QUANTITY; i++) {
        double value = solver.getState(step * i)[0];
        if (i > MIN_POINT_QUANTITY) {
            if (fabs(value) < stddev * 3) {
                smallValueCounter ++;
            } else {
                smallValueCounter = 0;
            }
            if (smallValueCounter > POINT_WINDOW) {
                break;
            }
        }
        trueValues.push_back(value);
    }
    pointsQuantity = trueValues.size() - POINT_WINDOW;
    std::cout << "Result pointQuantity in MSE: " << pointsQuantity << '\n';
}

double PendulumMSE::operator()(const Vector &v, bool cache) const {
    double res = 0;

    auto compareSystem = systemFabric->produce(v);
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

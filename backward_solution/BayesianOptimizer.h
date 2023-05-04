//
// Created by u5ele55 on 03.05.23.
//

#pragma once

#include "GaussianProcesses.h"
#include "PendulumMSE.h"
#include <functional>

class BayesianOptimizer {
public:
    BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp);

    Vector step();
    Vector getArgmin();
private:
    Vector acquisitionUCB(const Vector &mean, Vector stddev, double devCoef = 1);

private:
    PendulumMSE &f;
    // std::vector<Vector> initX; 
    GaussianProcesses &gp;
    Vector argmin;
    double fMin;
};

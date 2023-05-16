//
// Created by u5ele55 on 03.05.23.
//

#pragma once

#include "GaussianProcesses.h"
#include "PendulumMSE.h"
#include <functional>

class BayesianOptimizer {
public:
    BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, int startGeneration = 10);
    Vector step();
    
private:
    PendulumMSE &f;
    GaussianProcesses &gp;
    std::vector<Boundary> bounds;
    int startGeneration;
};

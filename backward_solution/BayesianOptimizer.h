//
// Created by u5ele55 on 03.05.23.
//

#pragma once

#include "GaussianProcesses.h"
#include "PendulumMSE.h"
#include "acquisition/IAcquisition.h"
#include <random>

class BayesianOptimizer {
public:
    BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, int startGeneration = 10);
    Vector step();
private:
    double acquisitionCall(const VectorXd& x, VectorXd& grad);
    Vector generateRandom();
private:
    PendulumMSE &f;
    GaussianProcesses &gp;
    std::vector<Boundary> bounds;
    int startGeneration;

    std::vector<std::uniform_real_distribution<>> distrs;
};

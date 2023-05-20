//
// Created by u5ele55 on 03.05.23.
//

#pragma once

#include "GaussianProcesses.h"
#include "IFunction.h"
#include "acquisition/IAcquisition.h"
#include <random>

#define GRADIENT_STEP 1e-7

class BayesianOptimizer {
public:
    BayesianOptimizer(IFunction &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, IAcquisition *acq, int startGeneration = 20);
    std::pair<Vector, double> step();
    Vector getArgmin() const;
private:
    double acquisitionCall(const VectorXd& x, VectorXd& grad);
    VectorXd generateRandom();
private:
    IFunction &f;
    GaussianProcesses &gp;
    std::vector<Boundary> bounds;
    IAcquisition *acq;
    int startGeneration;

    std::vector<std::uniform_real_distribution<>> distrs;
};
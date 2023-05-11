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

    std::vector<Vector> getChecked() const;

private:
    /**
     * Sample of acquisition function
     * */
    Vector acquisitionUCB(const Vector &mean, Vector stddev, double devCoef = 1);

    bool vectorChecked(const Vector &vec) const;

private:
    PendulumMSE &f;
    GaussianProcesses &gp;
    Vector argmin;
    std::vector<Vector> checkedDots;
    double fMin;
};

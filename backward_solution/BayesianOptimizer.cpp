//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>

BayesianOptimizer::BayesianOptimizer(std::function<double(Vector)> f, GaussianProcesses gp)
    : f(f)
    , gp(gp)
{
}

Vector BayesianOptimizer::acquisitionUCB(const Vector &mean, std::vector<Vector> stddev)
{
    auto space = gp.getSpace();
    int argmin = -1;
    long double minValue = mean[0];

    for (int i = 0; i < space.size(); i++) {
        if (mean[i] < minValue) {
            argmin = i;
        }
    }
    return gp.getSpace().at(argmin);
}

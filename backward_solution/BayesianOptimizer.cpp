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

Vector BayesianOptimizer::acquistionUCB(std::vector<Vector> mean, std::vector<Vector> stddev)
{
    auto space = gp.getSpace();
    double minLen = 1e1000;
    int argmin = -1;
    for (int i = 0; i < mean.size(); i++) {
        auto vec = mean[i] - stddev[i] * 2;
        double len = 0;
        for (int j = 0; j < vec.getShape().first; j++) {
            len += std::pow(vec[j], 2);
        }
        len = sqrt(len);
        if (len < minLen) {
            argmin = i;
        }
    }
    return gp.getSpace().at(argmin);
}

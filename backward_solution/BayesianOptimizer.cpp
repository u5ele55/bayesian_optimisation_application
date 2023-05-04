//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <iostream>

BayesianOptimizer::BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp)
    : f(f)
    , gp(gp)
{
}

Vector BayesianOptimizer::acquisitionUCB(const Vector &mean, Vector stddev, double devCoef)
{
    auto space = gp.getSpace();
    int argmin = -1;
    long double minValue = mean[0];

    for (int i = 0; i < space.size(); i++) {
        auto value = mean[i] - stddev[i] * devCoef;
        if (value < minValue) {
            argmin = i;
        }
    }
    return gp.getSpace().at(argmin);
}

Vector BayesianOptimizer::step() {
    std::cout << "Prediction calculation... \n";
    auto prediction = gp.predict();
    std::cout << "Predicted!\n";
    auto mean = prediction.first;
    Vector stddev = Vector(mean.getShape().first);

    for (int i = 0; i < stddev.getShape().first; i++) {
        stddev[i] = sqrt(prediction.second.at(i, i));
    }
    std::cout << "Going through space to find min...\n";
    auto x = acquisitionUCB(mean, stddev);
    double y = f(x);
    std::cout << "Fitting new data..\n";
    gp.fit(x, y);
    return x;
}

//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <iostream>

BayesianOptimizer::BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp)
    : f(f)
    , gp(gp)
    , argmin(gp.getSpace().dimensions())
    , fMin(1e300)
{
}

Vector BayesianOptimizer::acquisitionUCB(const Vector &mean, Vector stddev, double devCoef)
{
    auto space = gp.getSpace();
    double minValue = mean[0] - stddev[0] * devCoef;
    space.clear();
    Vector thisValue = space.next();
    Vector minPoint(thisValue);
    for (int i = 0; i < space.size(); i++) {
        auto value = mean[i] - stddev[i] * devCoef;
        if (value <= minValue) {
            std::cerr << "NEW MIN FOUND!\n";
            minPoint = thisValue;
            minValue = value;
        }
        thisValue = space.next();
    }

    return minPoint;
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
    auto x = acquisitionUCB(mean, stddev, 2);
    double y = f(x);
    std::cout << "Fitting new data: " << y << "\n";
    gp.fit(x, y);
    if (y < fMin) {
        argmin = x;
        fMin = y;
    }
    return x;
}

Vector BayesianOptimizer::getArgmin() {
    return argmin;
}

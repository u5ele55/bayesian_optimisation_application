//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <iostream>
#include <random>

BayesianOptimizer::BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp)
        : f(f),
          gp(gp),
          argmin(4), // TODO!!!!
          fMin(1e300) {
}

Vector BayesianOptimizer::acquisitionUCB(const Vector &mean, Vector stddev, double devCoef) {
    
    // mda
}


bool BayesianOptimizer::vectorChecked(const Vector &vec) const
{
    for (const auto &v : checkedDots) {
        if (v == vec) {
            return true;
        }
    }
    return false;
}

Vector BayesianOptimizer::step() {
    auto prediction = gp.predict({});
    auto mean = prediction.first;
    Vector stddev = Vector(mean.getShape().first);

    for (int i = 0; i < stddev.getShape().first; i++) {
        stddev[i] = sqrt(prediction.second.at(i, i));
    }
    auto x = acquisitionUCB(mean, stddev, 2);
    double y = f(x);
    std::cout << "Fitting new data with function value " << y << "\n";
    //gp.fit(x, y);
    if (y < fMin) {
        argmin = x;
        fMin = y;
    }
    return x;
}

Vector BayesianOptimizer::getArgmin() {
    return argmin;
}

std::vector<Vector> BayesianOptimizer::getChecked() const
{
    return checkedDots;
}

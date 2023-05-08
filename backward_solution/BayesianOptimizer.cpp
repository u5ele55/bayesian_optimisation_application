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
          argmin(gp.getSpace().dimensions()),
          fMin(1e300) {
}

Vector BayesianOptimizer::acquisitionUCB(const Vector &mean, Vector stddev, double devCoef) {
    auto space = gp.getSpace();
    double minValue = mean[0] - stddev[0] * devCoef;
    space.clear();
    Vector thisValue = space.next();
    Vector minPoint(thisValue);
    for (int i = 0; i < space.size(); i++) {
        auto value = mean[i] - stddev[i] * devCoef;
        if (value <= minValue) {
            minPoint = thisValue;
            minValue = value;
        }
        thisValue = space.next();
    }

    if (vectorChecked(minPoint)) {
        std::cout << "Aha! it was checked: " << minPoint << '\n';
        minPoint = findRandomUncheckedPoint(space);
        std::cout << "Instead, exploring at " << minPoint << '\n';
    }

    checkedDots.push_back(minPoint);
    return minPoint;
}

Vector BayesianOptimizer::findRandomUncheckedPoint(LinearSpace &space)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> uniformDistr(0, space.size() - 1);

    size_t randomIndex = uniformDistr(rng);
    Vector randomUnchecked = space.at(randomIndex);

    while (vectorChecked(randomUnchecked)) {
        randomIndex = uniformDistr(rng);
        randomUnchecked = space.at(randomIndex);
    }
    return randomUnchecked;
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
    auto prediction = gp.predict();
    auto mean = prediction.first;
    Vector stddev = Vector(mean.getShape().first);

    for (int i = 0; i < stddev.getShape().first; i++) {
        stddev[i] = sqrt(prediction.second.at(i, i));
    }
    auto x = acquisitionUCB(mean, stddev, 2);
    double y = f(x);
    std::cout << "Fitting new data with function value " << y << "\n";
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

std::vector<Vector> BayesianOptimizer::getChecked() const
{
    return checkedDots;
}

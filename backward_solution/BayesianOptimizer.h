//
// Created by u5ele55 on 03.05.23.
//

#pragma once

#include "GaussianProcesses.h"
#include <functional>

class BayesianOptimizer {
public:
    BayesianOptimizer(std::function<double(Vector)> f, GaussianProcesses gp);

private:
    Vector acquistionUCB(std::vector<Vector> mean, std::vector<Vector> stddev);

private:
    std::function<double(Vector)> f; 
    // std::vector<Vector> initX; 
    GaussianProcesses gp;
};

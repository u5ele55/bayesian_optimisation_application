//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <iostream>
#include <random>

BayesianOptimizer::BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, int startGeneration)
        : f(f),
          gp(gp),
          bounds(bounds),
          startGeneration(startGeneration) {
}


Vector BayesianOptimizer::step() {
    
}
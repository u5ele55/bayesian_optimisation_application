#pragma once

#include "BayesianOptimizer.h"
#include "../utils/logs/AbstractLogger.h"

class OptimizerEpoch {
public:
    OptimizerEpoch(BayesianOptimizer &bo, AbstractLogger *logger, int expectedImprovement = 10, int maxIterations = 30);

    /**
     * Makes bayesian optimization steps until MSE decreases
     * */
    Vector iterate();

private:
    BayesianOptimizer &bo;
    int expectedImprovement;
    int maxIterations;
    AbstractLogger *logger;
};

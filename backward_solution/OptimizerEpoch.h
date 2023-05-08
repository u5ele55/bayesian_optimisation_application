#pragma once

#include "BayesianOptimizer.h"
#include "../utils/logs/AbstractLogger.h"

class OptimizerEpoch {
public:
    OptimizerEpoch(BayesianOptimizer &bo, AbstractLogger *logger);

    /**
     * Makes bayesian optimization steps until MSE decreases
     * */
    Vector iterate();

private:
    BayesianOptimizer &bo;
    AbstractLogger *logger;
};

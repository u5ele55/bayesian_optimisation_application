#pragma once

#include "BayesianOptimizer.h"
#include "../utils/logs/ILogger.h"

class OptimizerEpoch {
public:
    OptimizerEpoch(BayesianOptimizer &bo, ILogger * logger);
    /// @brief makes bayesian optimization steps until mse decreases 
    Vector iterate();

private:
    BayesianOptimizer &bo;
    ILogger * logger;
};

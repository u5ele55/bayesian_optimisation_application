#pragma once

#include "BayesianOptimizer.h"

class OptimizerEpoch {
public:
    OptimizerEpoch(BayesianOptimizer &bo);
    /// @brief makes bayesian optimization steps until mse decreases 
    Vector iterate();

private:
    BayesianOptimizer &bo;
};

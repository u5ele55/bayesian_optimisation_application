#include <iostream>
#include "OptimizerEpoch.h"
#include "../utils/SolutionCache.h"

OptimizerEpoch::OptimizerEpoch(BayesianOptimizer &bo, AbstractLogger *logger, int expectedImprovement, int maxIterations)
        : bo(bo),
          logger(logger),
          expectedImprovement(expectedImprovement),
          maxIterations(maxIterations) {
}

Vector OptimizerEpoch::iterate() {
    int countdown = expectedImprovement;
    auto epochMinimum = bo.getArgmin();
    for (int i = 0; i < maxIterations && countdown--; i++) {
        std::cout << "Step " << i << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;

        if (!(bo.getArgmin() == epochMinimum)) {
            countdown = expectedImprovement;
            epochMinimum = bo.getArgmin();
        }
        logger->printSystem(SolutionCache::getInstance().get(prediction));
    }
    std::cout << "Minimum for epoch: " << epochMinimum << '\n';
    return epochMinimum;
}

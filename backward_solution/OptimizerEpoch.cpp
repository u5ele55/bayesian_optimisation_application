#include <iostream>
#include "OptimizerEpoch.h"
#include "../utils/SolutionCache.h"

OptimizerEpoch::OptimizerEpoch(BayesianOptimizer &bo, ILogger * logger)
        : bo(bo), 
        logger(logger) {
}

Vector OptimizerEpoch::iterate()
{
    const int expectedImprovementIterations = 7; // expected iteration quantity for improvement
    int countdown = expectedImprovementIterations; 
    int i = 0;
    auto epochMinimum = bo.getArgmin();
    while (countdown--) {
        std::cout << "Step " << i++ << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;

        if (!(bo.getArgmin() == epochMinimum)) {
            countdown = expectedImprovementIterations;
            epochMinimum = bo.getArgmin();
        }
        printSystem(logger->stream(), SolutionCache::getInstance().get(prediction));
    }
    std::cout << "Minimum for epoch: " << epochMinimum << '\n';
    return epochMinimum;
}

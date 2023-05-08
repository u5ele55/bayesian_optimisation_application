#include <iostream>
#include "OptimizerEpoch.h"

OptimizerEpoch::OptimizerEpoch(BayesianOptimizer &bo)
        : bo(bo) {
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
        //printSystem(output, SolutionCache::getInstance().get(prediction));
    }
    std::cout << "Minimum for epoch: " << epochMinimum << '\n';
    return epochMinimum;
}

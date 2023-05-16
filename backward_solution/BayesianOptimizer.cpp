//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <Eigen/Core>
#include <iostream>
#include <random>
#include <LBFGSB.h> 

BayesianOptimizer::BayesianOptimizer(PendulumMSE &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, int startGeneration)
        : f(f),
          gp(gp),
          bounds(bounds),
          startGeneration(startGeneration) {
    
    for (const auto &b : bounds) {
        distrs.push_back(std::uniform_real_distribution<>{b.min, b.max+3e-7});
    }
}


Vector BayesianOptimizer::step() {
    // :::::::Optimize acq:::::::
    // `startGeneration` random points : 
    // iterate through them

    Vector xBest(bounds.size());
    double yBest = 0;
 
    LBFGSpp::LBFGSBParam<double> param;
    param.epsilon = 1e-3;
    param.max_iterations = 20;
    LBFGSpp::LBFGSBSolver<double> solver(param);  // New solver class
 
    for (int i = 0; i < startGeneration; i ++) {
        double localYBest;
        auto initialGuess = generateRandom();
        // minimize for every point
        VectorXd lb = VectorXd::Zero(bounds.size());
        VectorXd ub = VectorXd::Constant(bounds.size());

        for (int j = 0; j < bounds.size(); j ++) {
            lb[j] = bounds[j].min;
            ub[j] = bounds[j].max;
        }

        solver.minimize(acquisitionCall, initialGuess, localYBest, lb, ub);
        // store best result
    }


    // fit it into gp
    gp.fit({xBest}, {yBest});
}

double BayesianOptimizer::acquisitionCall(const VectorXd &x, VectorXd &grad)
{
    return 0.0;
}

Vector BayesianOptimizer::generateRandom() 
{
    static std::default_random_engine e;
    
    Vector r(bounds.size());

    for(int i = 0; i < bounds.size(); i ++) {
        r[i] = distrs[i](e);
    }

    return r;
}

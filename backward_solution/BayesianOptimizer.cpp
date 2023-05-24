//
// Created by u5ele55 on 03.05.23.
//

#include "BayesianOptimizer.h"
#include <cmath>
#include <Eigen/Core>
#include <iostream>
#include <functional>
#include <random>
#include <LBFGSB.h> 

BayesianOptimizer::BayesianOptimizer(IFunction &f, GaussianProcesses &gp, const std::vector<Boundary> &bounds, IAcquisition *acq, int seed, int startGeneration)
        : f(f),
          gp(gp),
          bounds(bounds),
          startGeneration(startGeneration),
          acq(acq) {

    e.seed(seed);
    for (const auto &b : bounds) {
        distrs.push_back(std::uniform_real_distribution<>{b.min, b.max+3e-7});
    }
}


std::pair<Vector, double> BayesianOptimizer::step() {
    // :::::::Optimize acq:::::::
    // `startGeneration` random points : 
    // iterate through them

    Vector xBest(bounds.size());
    double acqBest = 1e300;
    
    // bounds
    VectorXd lb = VectorXd::Constant(bounds.size(), 0);
    VectorXd ub = VectorXd::Constant(bounds.size(), 0);
    for (int j = 0; j < bounds.size(); j ++) {
        lb[j] = bounds[j].min;
        ub[j] = bounds[j].max;
    }
 
    for (int i = 0; i < startGeneration; i ++) {
        LBFGSpp::LBFGSBParam<double> param;
        param.epsilon = 3e-4;
        param.max_iterations = 0;
        param.max_linesearch = 40;
        LBFGSpp::LBFGSBSolver<double> solver(param); 
        double localAcqBest;
        auto initialGuess = generateRandom();

        // minimize for every point
        auto acqCall = [this](const VectorXd &x, VectorXd &grad) -> double {
            return this->acquisitionCall(x, grad);
        };
        
        try {
            // std::cout << "---\n";
            // VectorXd tmp = VectorXd::Zero(4);
            // std::cout << "BEFORE " <<  initialGuess << "\nacq " << acqCall(initialGuess, tmp) << "\n";
            solver.minimize(acqCall, initialGuess, localAcqBest, lb, ub);
            // std::cout << "AFTER " << initialGuess << "\nacq " << localAcqBest << "\n";

            // store best result
            if (localAcqBest < acqBest) {
                acqBest = localAcqBest;
                xBest = initialGuess;
            }
        } catch(const std::runtime_error &err) {
            // its fine
            // std::cerr << "Generation " << i << " has not done with error: " << err.what() << "\n";
        }
    }

    // fit it into gp
    auto fCall = f(xBest);
    gp.fit({xBest}, {fCall});
    
    return {xBest, fCall};
}

Vector BayesianOptimizer::getArgmin() const
{
    return gp.getArgmin();
}

double BayesianOptimizer::acquisitionCall(const VectorXd &x, VectorXd &grad)
{
    Vector xV(0);
    xV = x;
    // std::cout << x << "\n";
    // std::cout << xV << "\n";

    auto predict = gp.predict({xV});
    // std::cout << "PREDICT " << predict.first << " " << predict.second << "\n";

    double mean = predict.first[0]; // 1d vector
    double std = predict.second[0];
    double value = (*acq)(gp.getMinY(), mean, std);

    for(int i = 0; i < bounds.size(); i ++) {
        Vector shiftedX = xV;
        shiftedX[i] += GRADIENT_STEP;

        predict = gp.predict({shiftedX});
        mean = predict.first[0];
        std = predict.second[0];

        grad[i] = ((*acq)(gp.getMinY(), mean, std) - value) / GRADIENT_STEP;
    }

    return value;
}

VectorXd BayesianOptimizer::generateRandom() 
{

    VectorXd r = VectorXd::Constant(bounds.size(), 0);

    for(int i = 0; i < bounds.size(); i ++) {
        r[i] = distrs[i](e);
    }

    return r;
}
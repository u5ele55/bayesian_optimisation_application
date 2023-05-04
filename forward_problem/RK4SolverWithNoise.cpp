#include "RK4SolverWithNoise.h"

#include <random>

RK4SolverWithNoise::RK4SolverWithNoise(System &system, double stddev, double step)
        : RK4ForwardSolver(system, step),
          stddev(stddev) {
}


Vector RK4SolverWithNoise::getState(double time)
{
    auto pureState = AbstractForwardSolver::getState(time);
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    
    std::normal_distribution<double> d(0, stddev); 
    double noise1 = d(gen), noise2 = d(gen); 

    return pureState + Vector{noise1, noise2};
}

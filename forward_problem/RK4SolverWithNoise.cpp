#include "RK4SolverWithNoise.h"

#include <iostream>

RK4SolverWithNoise::RK4SolverWithNoise(System &system, double stddev, double step)
        : RK4ForwardSolver(system, step),
          stddev(stddev),
          gen(rd()),
          normalDistr(0, stddev) {
}


Vector RK4SolverWithNoise::getState(double time)
{
    auto pureState = AbstractForwardSolver::getState(time);
    double noise1 = normalDistr(gen), noise2 = normalDistr(gen); 
    return pureState + Vector{noise1, noise2};
}

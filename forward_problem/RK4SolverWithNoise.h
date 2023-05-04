#pragma once

#include "RK4Solver.h"

class RK4SolverWithNoise : public RK4ForwardSolver {
public:
    explicit RK4SolverWithNoise(System &system, double stddev, double step = 1e-2);
    Vector getState(double time);
private:
    double stddev;
};

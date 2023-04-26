#pragma once

#include "AbstractForwardSolver.h"

class RK4ForwardSolver : public AbstractForwardSolver {
public:
    RK4ForwardSolver(System &system, double step = 1e-2);
    void methodStep(Vector &state, double step);
private:
    Vector k1, k2, k3, k4;
};

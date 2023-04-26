#pragma once

#include "system.h"

class AbstractForwardSolver {
public:
    AbstractForwardSolver(System &system, double step = 1e-2);

    virtual void methodStep(Vector &state, double step) = 0;

    Vector getState(double time);
protected:
    double step;
    System &system;
    Vector state;
};
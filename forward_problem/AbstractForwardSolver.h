#pragma once

#include "System.h"

class AbstractForwardSolver {
public:
    explicit AbstractForwardSolver(System &system, double step = 1e-2);

    virtual void methodStep(Vector &state, double step) = 0;

    virtual Vector getState(double time);
protected:
    double step;
    System &system;
    Vector state;
};
#include "AbstractForwardSolver.h"

AbstractForwardSolver::AbstractForwardSolver(System &system, double step)
        : step(step), system(system), state(system.getInitialState().getShape().first) {}

Vector AbstractForwardSolver::getState(double time) {
    for (int i = 0; i < state.getShape().first; i++) {
        state[i] = system.getInitialState()[i];
    }

    for (int _ = 1; _ < static_cast<int>(time / step) + 1; _++) {
        methodStep(state, step);
    }

    // recalculate more precisely for case when t != self.h * k for some whole k
    double wholePart = step * static_cast<int>(time / step);
    double timeDiff = time - wholePart;

    if (timeDiff != 0) {
        methodStep(state, timeDiff);
    }

    return state;
}

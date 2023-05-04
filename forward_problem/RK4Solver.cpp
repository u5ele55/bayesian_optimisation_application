#include "RK4Solver.h"

RK4ForwardSolver::RK4ForwardSolver(System &system, double step)
        : AbstractForwardSolver(system, step), k1(state.getShape().first), k2(state.getShape().first),
          k3(state.getShape().first), k4(state.getShape().first) {}

void RK4ForwardSolver::methodStep(Vector &state, double step) {
    k1 = state;
    system.f(k1);

    k2 = state + k1 * (step / 2);
    system.f(k2);

    k3 = state + k2 * (step / 2);
    system.f(k3);

    k4 = state + k3 * step;
    system.f(k4);

    state += (k1 + k2 * 2 + k3 * 2 + k4) * (step / 6);
}

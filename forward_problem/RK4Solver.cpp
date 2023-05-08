#include "RK4Solver.h"

RK4ForwardSolver::RK4ForwardSolver(System &system, double step)
        : AbstractForwardSolver(system, step),
          k1(state.getShape().first),
          k2(state.getShape().first),
          k3(state.getShape().first),
          k4(state.getShape().first) {}

void RK4ForwardSolver::methodStep(Vector &state, double step) {
    k1 = state;
    system.f(k1);

    //k2 = state + k1 * (step / 2);
    for(int i = 0; i < k2.getShape().first; i ++) {
      k2[i] = state[i] + k1[i] * step / 2;
    }
    
    system.f(k2);

    //k3 = state + k2 * (step / 2);
    for(int i = 0; i < k3.getShape().first; i ++) {
      k3[i] = state[i] + k2[i] * step / 2;
    }
    system.f(k3);

    //k4 = state + k3 * step;
    for(int i = 0; i < k4.getShape().first; i ++) {
      k4[i] = state[i] + k3[i] * step;
    }
    system.f(k4);

    //state += (k1 + k2 * 2 + k3 * 2 + k4) * (step / 6);
    for(int i = 0; i < k1.getShape().first; i ++) {
      state[i] = state[i] + (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]) * step / 6;
    }
}

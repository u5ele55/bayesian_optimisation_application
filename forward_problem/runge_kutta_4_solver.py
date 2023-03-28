import numpy as np
from forward_problem.solver import AbstractForwardSolver


class RungeKutta4Solver(AbstractForwardSolver):
    ''' Concrete solver for forward problem. Implements RK4 method '''
    def __init__(self, system, step=0.01):
        super().__init__(system, step)
        self.k_1, self.k_2, self.k_3, self.k_4 = ( np.zeros(system.initial_state.shape, float) for _ in range(4) )

    def method_step(self, state: np.ndarray, step: float):
        ''' Implementation of RK4 method step. Changes `state` vector '''
        for i in range(len(state)):
            self.k_1[i] = state[i]
            
        self.system.f(self.k_1)

        self.k_2 = state + step * self.k_1 / 2
        self.system.f(self.k_2)

        self.k_3 = state + step * self.k_2 / 2
        self.system.f(self.k_3)

        self.k_4 = state + step * self.k_3
        self.system.f(self.k_4)

        state += step * (self.k_1 + 2*self.k_2 + 2*self.k_3 + self.k_4) / 6
    
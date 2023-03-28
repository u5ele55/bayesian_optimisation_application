import numpy as np
from forward_problem.solver import AbstractForwardSolver


class RungeKutta4Solver(AbstractForwardSolver):
    ''' Concrete solver for forward problem. Implements RK4 method '''
    def __init__(self, system, step=0.01):
        super().__init__(system, step)
        self.k_1 = self.k_2 = self.k_3 = self.k_4 = ( np.array([0,0]) for _ in range(4) )

    def method_step(self, state: np.ndarray, step: float):
        ''' Implementation of RK4 method step. Changes `state` vector '''
        self.k_1[0] = state[0]
        self.k_1[1] = state[1]
        self.system.f(self.k_1)

        self.k_2 = state + step * self.k_1 / 2
        self.system.f(self.k_2)

        self.k_3 = state + step * self.k_2 / 2
        self.system.f(self.k_3)

        self.k_4 = state + step * self.k_3
        self.system.f(self.k_4)

        state += step * (self.k_1 + 2*self.k_2 + 2*self.k_3 + self.k_4) / 6
    
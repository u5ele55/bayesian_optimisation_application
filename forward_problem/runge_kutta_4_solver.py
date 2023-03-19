from forward_problem.solver import AbstractForwardSolver

class RungeKutta4Solver(AbstractForwardSolver):
    ''' Concrete solver for forward problem. Implements RK4 method '''
    def __init__(self, system, step=0.01, store_values=True):
        super().__init__(system, step, store_values)
        self.k_1 = self.k_2 = self.k_3 = self.k_4 = 0

    def method_step(self, state, step: float):
        ''' Solves problem with RK4 method '''
        self.k_1 = self.system.f(state)
        self.k_2 = self.system.f(state + step * self.k_1 / 2)
        self.k_3 = self.system.f(state + step * self.k_2 / 2)
        self.k_4 = self.system.f(state + step * self.k_3)

        return state + step * (self.k_1 + 2*self.k_2 + 2*self.k_3 + self.k_4) / 6
    
from forward_problem.solver import AbstractForwardSolver

class RungeKutta4Solver(AbstractForwardSolver):
    ''' Solves problem with RK4 method '''
    def method_step(self, state, step: float):
        k_1 = self.system.f(state)
        k_2 = self.system.f(state + step * k_1 / 2)
        k_3 = self.system.f(state + step * k_2 / 2)
        k_4 = self.system.f(state + step * k_3)

        return state + step * (k_1 + 2*k_2 + 2*k_3 + k_4) / 6
from forward_problem.solver import ForwardSolver

class RungeKutta4Solver(ForwardSolver):
    
    def methodStep(self, state, dt: float):
        k1 = self.system.f(state)
        k2 = self.system.f(state + dt * k1 / 2)
        k3 = self.system.f(state + dt * k2 / 2)
        k4 = self.system.f(state + dt * k3)

        return state + dt * (k1 + 2*k2 + 2*k3 + k4) / 6
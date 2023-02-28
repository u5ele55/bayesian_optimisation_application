from forward_problem.solver import ForwardSolver

class RungeKutta4Solver(ForwardSolver):
    def getState(self, t: float):
        if t < self.lastEvaluatedMoment:
            # TODO recalculate more precisely 
            dh = t - self.h * (t // self.h)

            return self.values[self.h * (t // self.h)]
        
        state = self.values[self.lastEvaluatedMoment]

        for i in range(int(self.lastEvaluatedMoment / self.h) + 1, int(t / self.h) + 1):
            state = self.methodStep(state, self.h)
            self.values[self.h * i] = state

        # TODO recalculate more precisely for case when t != self.h * k for some whole k
        
        return self.values[self.h * (t // self.h)]
    
    def methodStep(self, state, dt: float):
        k1 = self.system.f(state)
        k2 = self.system.f(state + dt * k1 / 2)
        k3 = self.system.f(state + dt * k2 / 2)
        k4 = self.system.f(state + dt * k3)

        return state + dt * (k1 + 2*k2 + 2*k3 + k4) / 6
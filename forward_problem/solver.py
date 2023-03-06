
class AbstractForwardSolver:
    def __init__(self, system, h = 1e-2):
        self.h = h
        self.system = system
        self.values = {0: system.initialState}
        self.lastEvaluatedMoment = 0

    def getState(self, t: float):
        ''' Returns state in time = `t` '''
        if t <= self.lastEvaluatedMoment:
            # recalculate more precisely 
            dh = t - self.h * int(t / self.h)
            preciseState = self.methodStep(self.values[self.h * int(t / self.h)], dh)
            return preciseState
        
        state = self.values[self.lastEvaluatedMoment]

        for i in range(int(self.lastEvaluatedMoment / self.h) + 1, int(t / self.h) + 1):
            state = self.methodStep(state, self.h)
            self.values[self.h * i] = state
        self.lastEvaluatedMoment = int(t / self.h) * self.h

        # recalculate more precisely for case when t != self.h * k for some whole k
        dh = t - self.h * int(t / self.h)
        if dh != 0:
            preciseState = self.methodStep(self.values[self.h * (t // self.h)], dh)
            return preciseState
        return self.values[self.h * int(t / self.h)]
    
    # factory method
    def methodStep(self, state, dt: float):
        ''' One step of the method '''
        raise NotImplementedError("Use concrete forward problem solver")
    
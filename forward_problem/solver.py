
class ForwardSolver:
    def __init__(self, system, h = 1e-2):
        self.h = h
        self.system = system
        self.values = {0: system.initialState}
        self.lastEvaluatedMoment = 0

    def getState(self, t: float):
        ''' Returns state in time = `t` '''
        pass

    def methodStep(self, state, dt: float):
        ''' One step of the method '''
        pass
    
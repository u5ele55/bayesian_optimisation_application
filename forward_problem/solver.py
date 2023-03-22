''' Abstract forward solver '''

class AbstractForwardSolver:
    ''' Abstract forward problem solver, has implemented `get_state` 
    method for runge-kutta methods and unimplemented `method_step` 
    method (has to be implemented in concrete solvers)'''
    def __init__(self, system, step = 1e-2):
        self.step = step
        self.system = system

    def get_state(self, time: float):
        ''' Returns state in time = `t` '''
        state = self.system.initial_state

        for _ in range(1, int(time / self.step) + 1):
            state = self.method_step(state, self.step)
        
        # recalculate more precisely for case when t != self.h * k for some whole k
        whole_part = self.step * int(time / self.step)
        time_diff = time - whole_part
        if time_diff != 0:
            precise_state = self.method_step(state, time_diff)
            return precise_state
        return state

    def get_states(self, time: float) -> list:
        ''' Returns map of states up to nearest to `time` whole multiple of `step` '''
        values = {}
        state = self.system.initial_state

        for i in range(1, int(time / self.step) + 1):
            state = self.method_step(state, self.step)
            values[self.step * i] = state

        return values

    # factory method
    def method_step(self, state, step: float):
        ''' One step of the method '''
        raise NotImplementedError("Use concrete forward problem solver")
    
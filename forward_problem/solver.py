''' Abstract forward solver '''

class AbstractForwardSolver:
    ''' Abstract forward problem solver, has implemented `get_state` 
    method for runge-kutta methods and unimplemented `method_step` 
    method (has to be implemented in concrete solvers)'''
    def __init__(self, system, step = 1e-2, store_values = True):
        self.step = step
        self.system = system
        self.store_values = store_values

        if self.store_values:
            self.values = {0: system.initial_state}
            self.last_evaluated_moment = 0

    def get_state(self, time: float):
        ''' Returns state in time = `t` '''
        whole_part = self.step * int(time / self.step)
        
        if self.store_values and time <= self.last_evaluated_moment:
            # recalculate more precisely
            time_diff = time - whole_part
            precise_state = self.method_step(self.values[whole_part], time_diff)
            return precise_state
        
        if self.store_values:
            state = self.values[self.last_evaluated_moment]
            start_moment = int(self.last_evaluated_moment / self.step) + 1
        else:
            state = self.system.initial_state
            start_moment = 1

        for i in range(start_moment, int(time / self.step) + 1):
            state = self.method_step(state, self.step)
            if self.store_values:
                self.values[self.step * i] = state
        
        if self.store_values:
            self.last_evaluated_moment = int(time / self.step) * self.step

        # recalculate more precisely for case when t != self.h * k for some whole k
        time_diff = time - whole_part
        if time_diff != 0:
            precise_state = self.method_step(state, time_diff)
            return precise_state
        return state

    # factory method
    def method_step(self, state, step: float):
        ''' One step of the method '''
        raise NotImplementedError("Use concrete forward problem solver")
    
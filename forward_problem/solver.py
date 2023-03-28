''' Abstract forward solver '''
import numpy as np

class AbstractForwardSolver:
    ''' Abstract forward problem solver, has implemented `get_state` 
    method for runge-kutta methods and unimplemented `method_step` 
    method (has to be implemented in concrete solvers)'''
    def __init__(self, system, step = 1e-2):
        self.step = step
        self.system = system
        self.state = np.array([0,0])

    def get_state(self, time: float):
        ''' Returns state in time = `time` '''
        self.state = np.copy(self.system.initial_state)

        for _ in range(1, int(time / self.step) + 1):
            self.method_step(self.state, self.step)

        # recalculate more precisely for case when t != self.h * k for some whole k
        whole_part = self.step * int(time / self.step)
        time_diff = time - whole_part

        if time_diff != 0:
            self.method_step(self.state, time_diff)

        return self.state

    def get_states(self, time: float) -> dict[float, np.ndarray]:
        ''' Returns map of states up to nearest to `time` whole multiple of `step` '''
        values = {}
        self.state = np.copy(self.system.initial_state)

        for i in range(1, int(time / self.step) + 1):
            self.method_step(self.state, self.step)
            values[self.step * i] = np.copy(self.state)

        return values

    # factory method
    def method_step(self, state: np.ndarray, step: float):
        ''' One step of the method '''
        raise NotImplementedError("Use concrete forward problem solver")
    
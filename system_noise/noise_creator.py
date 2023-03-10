''' Abstract noise creator class '''
from forward_problem.solver import AbstractForwardSolver

class AbstractNoiseCreator:
    ''' Adds noise to `solver` output '''
    def __init__(self, solver: AbstractForwardSolver):
        self.solver = solver

    def get_state(self, time):
        ''' Returns state of the system with noise '''
        state = self.solver.get_state(time)
        return self.noise_function(state, time)

    def noise_function(self, state, time: float):
        ''' Creates noise '''
        raise NotImplementedError()
    
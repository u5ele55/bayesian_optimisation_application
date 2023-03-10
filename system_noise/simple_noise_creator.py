''' Example of how noise can be applied to system '''
from math import sin
from system_noise.noise_creator import AbstractNoiseCreator
from forward_problem.dissipative_pendulum import PendulumState

class SimpleNoiseCreator(AbstractNoiseCreator):
    ''' Prototype of how noise creation should look like '''
    def noise_function(self, state: PendulumState, time) -> PendulumState:
        ''' Goofy example '''
        coeff = 1 + sin(time) / 20
        return state * coeff
    
''' Example of how noise can be applied to system '''
from system_noise.noise_creator import AbstractNoiseCreator
import numpy as np

class SimpleNoiseCreator(AbstractNoiseCreator):
    ''' Prototype of how noise creation should look like '''
    def noise_function(self, state: np.ndarray, time):
        ''' Goofy example '''
        coeff = 1 + np.sin(time) / 20
        return state * coeff
    
import numpy as np


class SquaredExponentialKernel:
    def __init__(self, sigma_f: float = 1.0, length: float = 1.0):
        self.sigma_f = sigma_f
        self.length = length

    def __call__(self, argument_1: np.array, argument_2: np.array) -> float:
        return float(
            self.sigma_f *
            np.exp(
                -(np.linalg.norm(argument_1 - argument_2) ** 2) / (2 * self.length ** 2)
            )
        )



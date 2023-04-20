import numpy as np
from bayesian_optimization.utils.gp import GPR
from bayesian_optimization.utils.acquisition_functions import acq_ucb
from bayesian_optimization.utils.kernels import SquaredExponentialKernel


class BayesianOptimizer:
    def __init__(self, func, init_x, space, *, acq=acq_ucb, gp=GPR()):
        self.f = func
        self.X = init_x
        self.Y = self.f(self.X)
        self.space = space
        self.acq = acq
        # self._gp = GPR(kernel=kernel, noise=noise)
        self._gp = gp

    def step(self):
        self._gp.fit(self.X, self.Y)
        prediction = self._gp.predict(self.space)
        # var = prediction['variance']
        # cov_mat = prediction['covariance_matrix']
        mean = prediction['mean']
        stddev = np.sqrt(prediction['variance'])

        point = self.acq(self.space, mean, stddev, 2.0)
        self.X = np.append(self.X, point)
        self.Y = np.append(self.Y, self.f(point))
        return prediction

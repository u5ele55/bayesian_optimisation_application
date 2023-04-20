import numpy as np


def acq_ucb(values, mu, div, coef=1.0):
    argmin = np.argmin(mu - coef * div)
    return values[argmin]

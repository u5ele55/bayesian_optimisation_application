import math
import matplotlib.pyplot as plt
import numpy as np
from bayesian_optimization.core import BayesianOptimizer
from bayesian_optimization.utils.kernels import SquaredExponentialKernel
from bayesian_optimization.utils.gp import GPR


def test_1d():
    np.random.seed(42)

    sigma = 0.8  # noise sigma
    domain = (-6, 6)  # x_min, x_max

    initial_n = 4  # initial points quantity
    iter_n = 7  # quantity of iterations
    ny = 5  # quantity of posterior functions

    def f(x):
        noise = np.random.normal(0.0, sigma)
        return (math.e ** (-x / 5) * 2 * np.sin(2 * x) + noise).flatten()

    init_x = np.random.uniform(domain[0], domain[1], initial_n)
    space = np.linspace(domain[1], domain[0], 100)
    bayes_opt = BayesianOptimizer(f, init_x, space, gp=GPR(kernel=SquaredExponentialKernel(sigma_f=5.0), noise=sigma))

    prediction = None
    for i in range(iter_n):
        prediction = bayes_opt.step()

    μ2 = prediction['mean']
    σ2 = prediction['variance']
    Σ2 = prediction['covariance_matrix']

    # Plot taken from https://peterroelants.github.io/posts/gaussian-process-tutorial/

    # Draw some samples of the posterior
    y2 = np.random.multivariate_normal(mean=μ2, cov=Σ2, size=ny)

    fig, (ax1, ax2) = plt.subplots(
        nrows=2, ncols=1, figsize=(6, 6))
    # Plot the distribution of the function (mean, covariance)
    ax1.plot(space, f(space), 'b--', label='$sin(x)$')
    ax1.fill_between(space.flat, μ2 - 2 * σ2, μ2 + 2 * σ2, color='red',
                     alpha=0.15, label='$2 \sigma_{2|1}$')
    ax1.plot(space, μ2, 'r-', lw=2, label='$\mu_{2|1}$')
    ax1.plot(bayes_opt.X, bayes_opt.Y, 'ko', linewidth=2, label='$(x_1, y_1)$')
    ax1.set_xlabel('$x$', fontsize=13)
    ax1.set_ylabel('$y$', fontsize=13)
    ax1.set_title('Distribution of posterior and prior data.')
    ax1.set_xlim([domain[0], domain[1]])
    # Plot some samples from this function
    ax2.plot(space, y2.T, '-')
    ax2.set_xlabel('$x$', fontsize=13)
    ax2.set_ylabel('$y$', fontsize=13)
    ax2.set_title('5 different function realizations from posterior')
    ax2.set_xlim([domain[0], domain[1]])
    plt.tight_layout()
    plt.show()
    #

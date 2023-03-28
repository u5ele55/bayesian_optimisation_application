import matplotlib.pyplot as plt
import numpy as np

from forward_problem.dissipative_pendulum import DissipativePendulum
from forward_problem.runge_kutta_4_solver import RungeKutta4Solver

def test():
    ''' Test forward problem solver '''
    system = DissipativePendulum(0.5, 0.3, 3.14/3, 0.2)
    solver = RungeKutta4Solver(system)

    solver.get_state(4)
    vals = [np.copy(solver.get_state(i / 100)) for i in range(1800)]

    plt.plot([i/100 for i in range(1800)], [val[0] for val in vals])
    plt.show()
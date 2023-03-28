''' Testing noise applied to system '''
import matplotlib.pyplot as plt
import numpy as np

from system_noise.simple_noise_creator import SimpleNoiseCreator
from forward_problem.runge_kutta_4_solver import RungeKutta4Solver
from forward_problem.dissipative_pendulum import DissipativePendulum

def test():
    ''' Test noise '''
    system = DissipativePendulum(0.5, 0.3, 3.14/3, 0.2)
    solver = RungeKutta4Solver(system, step=0.05)
    noiser = SimpleNoiseCreator(solver)

    # vals = [np.copy(solver.get_state(i / 100)) for i in range(1500)]
    # # same as
    vals = solver.get_states(15)
    vals_noise = [noiser.get_state( i / 10 ) for i in range(150)]

    plt.plot(vals.keys(), [val[0] for val in vals.values()])
    plt.scatter([i/10 for i in range(150)], [val[0] for val in vals_noise], s=1, c="#000000")
    plt.show()
    
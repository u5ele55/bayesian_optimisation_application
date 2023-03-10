''' Testing noise applied to system '''
import matplotlib.pyplot as plt

from system_noise.simple_noise_creator import SimpleNoiseCreator
from forward_problem.runge_kutta_4_solver import RungeKutta4Solver
from forward_problem.dissipative_pendulum import DissipativePendulum

def test():
    ''' Test noise '''
    system = DissipativePendulum(0.5, 0.3, 3.14/3, 0.2)
    solver = RungeKutta4Solver(system)
    noiser = SimpleNoiseCreator(solver)

    vals = [solver.get_state(i / 100) for i in range(4000)]
    vals_noise = [noiser.get_state( i / 100 ) for i in range(4000)]

    plt.plot([i/100 for i in range(4000)], [val.angle for val in vals])
    plt.plot([i/100 for i in range(4000)], [val.angle for val in vals_noise])
    plt.show()
    
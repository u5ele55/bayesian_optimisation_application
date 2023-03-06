from forward_problem.runge_kutta_4_solver import RungeKutta4Solver
from forward_problem.solver import AbstractForwardSolver
from forward_problem.dissipative_pendulum import DissipativePendulum

import matplotlib.pyplot as plt

# TESTING FORWARD PROBLEM SOLUTION

def test():
    

    system = DissipativePendulum(0.5, 0.3, 3.14/3, 0.2)
    solver = RungeKutta4Solver(system)

    solver.getState(4)
    vals = [solver.getState(i / 100) for i in range(4000)]
    
    plt.plot([i/100 for i in range(4000)], [val.angle for val in vals])
    plt.show()


''' Classes of system and its state '''
import math
import numpy as np

# For usual pendulum
# Iä + mgl sin(a) = 0, where a is an angle. I = ml**2 - inertia moment

# For dissipative pendulum
# Iä + kȧ + mgl sin(a) = 0, where k is dissipation coefficient
# => ä + cȧ + ω**2 sin(a) = 0, where ω = sqrt(g/l), c = k / I
# => ä = - cȧ - ω**2 sin(a)

# We obtain a system of DE's of first degree
# ȧ = o
# ȯ = - cȧ - ω**2 sin(a)

class DissipativePendulum:
    ''' Class for dissipative pendulum system. Stores parameters and DE of the system '''
    def __init__(self, omega: float, dissipation_coeffitient: float,
                 initial_angle: float, initial_angular_speed: float):
        self.omega_sq = omega**2
        self.dissip_coeff = dissipation_coeffitient
        self.initial_state = np.array([initial_angle, initial_angular_speed])

    def f(self, state: np.ndarray):
        ''' DE of the system. Changes `state` array '''
        #print(state[0], math.sin(state[0]))
        acceleration = -self.dissip_coeff * state[1] - self.omega_sq * math.sin(state[0])
        state[0] = state[1]       # d_angle = speed
        state[1] = acceleration   # d_speed = acceleration

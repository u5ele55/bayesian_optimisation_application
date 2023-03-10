''' Classes of system and its state '''
import math

# For usual pendulum
# Iä + mgl sin(a) = 0, where a is an angle. I = ml**2 - inertia moment

# For dissipative pendulum
# Iä + kȧ + mgl sin(a) = 0, where k is dissipation coefficient
# => ä + cȧ + ω**2 sin(a) = 0, where ω = sqrt(g/l), c = k / I
# => ä = - cȧ - ω**2 sin(a)

# We obtain a system of DE's of first degree
# ȧ = o
# ȯ = - cȧ - ω**2 sin(a)

class PendulumState:
    ''' Stores state of the system '''
    def __init__(self, angle: float, angular_speed: float):
        self.angle = angle
        self.speed = angular_speed
    def __add__(self, other):
        return PendulumState(self.angle + other.angle, self.speed + other.speed)
    def __mul__(self, mlt):
        return PendulumState(self.angle * mlt, self.speed * mlt)
    def __rmul__(self, mlt):
        return self.__mul__(mlt)
    def __truediv__(self, div):
        return PendulumState(self.angle / div, self.speed / div)


class DissipativePendulum:
    ''' Class for dissipative pendulum system. Stores parameters and DE of the system '''
    def __init__(self, omega: float, dissipation_coeffitient: float,
                 initial_angle: float, initial_angular_speed: float):
        self.omega_sq = omega**2
        self.dissip_coeff = dissipation_coeffitient
        self.initial_state = PendulumState(initial_angle, initial_angular_speed)

    def f(self, state: PendulumState):
        ''' DE of the system '''
        acceleration = -self.dissip_coeff * state.speed - self.omega_sq * math.sin(state.angle)
        d_angular_speed = acceleration
        d_angle = state.speed

        return PendulumState(d_angle, d_angular_speed)
    
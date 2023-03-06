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
    def __init__(self, angle: float, angularSpeed: float):
        self.angle = angle
        self.speed = angularSpeed
    def __add__(self, other):
        return PendulumState(self.angle + other.angle, self.speed + other.speed)
    def __mul__(self, mlt):
        return PendulumState(self.angle * mlt, self.speed * mlt)
    def __rmul__(self, mlt):
        return self.__mul__(mlt)
    def __truediv__(self, div):
        return PendulumState(self.angle / div, self.speed / div)
    

class DissipativePendulum:
    def __init__(self, omega: float, dissipation_coeffitient: float, initialAngle: float, initialAngularSpeed: float):
        self.omegaSq = omega**2
        self.dissipCoeff = dissipation_coeffitient
        self.initialState = PendulumState(initialAngle, initialAngularSpeed)
    
    def f(self, state: PendulumState):
        a = -self.dissipCoeff * state.speed - self.omegaSq * math.sin(state.angle)
        dAngularSpeed = a
        dAngle = state.speed

        return PendulumState(dAngle, dAngularSpeed)
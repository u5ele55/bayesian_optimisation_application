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

class DissipativePendulum:
    def __init__(self, omega: float, dissipation_coeffitient: float, initialAngle: float, initialAngularSpeed: float):
        self.omega = omega
        self.dissipCoeff = dissipation_coeffitient
        self.initialState = PendulumState(initialAngle, initialAngularSpeed)
    
    # TODO: add DE of system

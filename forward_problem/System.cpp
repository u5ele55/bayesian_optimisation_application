#include "System.h"

#include <cmath>

System::System(double omega, double dissipationCoefficient, double initialAngle, double initialAngularSpeed)
        : omega(omega),
          dissipationCoefficient(dissipationCoefficient),
          initialState({initialAngle, initialAngularSpeed}) {}

void System::f(Vector &state) const {
    double acceleration = -dissipationCoefficient * state[1] - omega * omega * sin(state[0]);
    state[0] = state[1];       // d_angle = speed
    state[1] = acceleration;   // d_speed = acceleration
}

Vector System::getInitialState() const {
    return initialState;
}

System::System(const Vector& vector)
        : omega(vector[0]),
          dissipationCoefficient(vector[1]),
          initialState({vector[2], vector[3]}) {}

Vector System::getInitializer() const {
    return Vector({omega, dissipationCoefficient, initialState[0], initialState[1]});
}

#include "System.h"

#include <cmath>

System::System(double omega, double dissipationCoefficient, double initialAngle, double initialAngularSpeed)
        : omegaSquared(omega * omega),
          dissipationCoefficient(dissipationCoefficient),
          initialState({initialAngle, initialAngularSpeed}) {}

void System::f(Vector &state) const {
    double acceleration = -dissipationCoefficient * state[1] - omegaSquared * sin(state[0]);
    state[0] = state[1];       // d_angle = speed
    state[1] = acceleration;   // d_speed = acceleration
}

Vector System::getInitialState() const {
    return initialState;
}

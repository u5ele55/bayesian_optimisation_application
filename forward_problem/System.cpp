#include "System.h"

#include <cmath>

System::System(double omega, double dissipationCoefficient, double initial_angle, double initial_angular_speed)
    : omegaSquared(omega*omega)
    , dissipationCoefficient(dissipationCoefficient)
    , initialState({initial_angle, initial_angular_speed})
{}

void System::f(Vector &state) const
{
    double acceleration = -dissipationCoefficient * state[1] - omegaSquared * sin(state[0]);
    state[0] = state[1];       // d_angle = speed
    state[1] = acceleration;   // d_speed = acceleration
}

Vector System::getInitialState() const
{
    return initialState;
}

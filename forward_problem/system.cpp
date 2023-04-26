#include "system.h"

#include "math.h"

System::System(double omega, double dissipation_coeffitient, double initial_angle, double initial_angular_speed)
    : omegaSquared(omega*omega)
    , dissipationCoeffitient(dissipation_coeffitient)
    , initialState({initial_angle, initial_angular_speed})
{}

void System::f(Vector &state) const
{
    double acceleration = -dissipationCoeffitient * state[1] - omegaSquared * sin(state[0]);
    state[0] = state[1];       // d_angle = speed
    state[1] = acceleration;   // d_speed = acceleration
}
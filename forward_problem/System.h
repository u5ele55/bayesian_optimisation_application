#pragma once

#include "../utils/Vector.h"

class System {
public:
    System(double omega, double dissipation_coeffitient, double initial_angle, double initial_angular_speed);

    void f(Vector &state) const;

    Vector getInitialState() const;
private:
    double omegaSquared;
    double dissipationCoeffitient;
    Vector initialState;
};
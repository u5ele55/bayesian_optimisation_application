#pragma once

#include "../utils/Vector.h"

class System {
public:
    System(double omega, double dissipationCoefficient, double initial_angle, double initial_angular_speed);

    void f(Vector &state) const;

    Vector getInitialState() const;
private:
    double omegaSquared;
    double dissipationCoefficient;
    Vector initialState;
};
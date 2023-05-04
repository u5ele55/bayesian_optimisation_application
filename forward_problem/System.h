#pragma once

#include "../utils/Vector.h"

class System {
public:
    System(double omega, double dissipationCoefficient, double initialAngle, double initialAngularSpeed);

    void f(Vector &state) const;

    Vector getInitialState() const;

private:
    double omegaSquared;
    double dissipationCoefficient;
    Vector initialState;
};
#pragma once

#include "../utils/Vector.h"

class System {
public:
    System(double omega, double dissipationCoefficient, double initialAngle, double initialAngularSpeed);

    explicit System(const Vector& vector);

    void f(Vector &state) const;

    Vector getInitialState() const;
private:
    double omega;
    double dissipationCoefficient;
    Vector initialState;
};
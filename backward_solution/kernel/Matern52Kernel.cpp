//
// Created by ormequ on 09.05.23.
//

#include <cmath>
#include "Matern52Kernel.h"

Matern52Kernel::Matern52Kernel(double sigma, double length)
        : length(length),
          sigma(sigma) {}

double Matern52Kernel::operator()(const Vector &a, const Vector &b) const {
    double dot = a.dot(b);
    double distance = sqrt(dot);
    double sqrt5 = sqrt(5);

    return sigma * (1 + sqrt5 * distance / length + 5 * dot / (3 * length * length)) * exp(-sqrt5 * distance / length);
}




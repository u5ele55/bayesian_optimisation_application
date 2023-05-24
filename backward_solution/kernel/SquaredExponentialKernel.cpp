//
// Created by ormequ on 27.04.23.
//

#include "SquaredExponentialKernel.h"
#include <iostream>

SquaredExponentialKernel::SquaredExponentialKernel(double sigma, double length)
        : sigma(sigma),
          length(length) {}

double SquaredExponentialKernel::operator()(const Vector &a, const Vector &b) const {
    return sigma * std::exp(-(a - b).dot(a - b) / (2 * length * length));
}


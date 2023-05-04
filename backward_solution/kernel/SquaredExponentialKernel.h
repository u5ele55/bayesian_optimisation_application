//
// Created by ormequ on 27.04.23.
//

#pragma once

#include "kernel/IKernel.h"
#include <cmath>

class SquaredExponentialKernel : public IKernel {
public:
    explicit SquaredExponentialKernel(double sigma = 1, double length = 1);
    double operator() (const Vector &a, const Vector &b) const final;
private:
    double sigma;
    double length;
};

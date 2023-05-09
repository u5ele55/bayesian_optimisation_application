//
// Created by ormequ on 09.05.23.
//

#pragma once


#include "IKernel.h"

class Matern52Kernel : public IKernel {
public:
    explicit Matern52Kernel(double sigma = 1, double length = 1);

    double operator()(const Vector &a, const Vector &b) const final;
private:
    double length;
    double sigma;
};

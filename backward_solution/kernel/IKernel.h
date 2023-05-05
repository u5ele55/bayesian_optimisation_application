//
// Created by ormequ on 27.04.23.
//

#pragma once

#include "../../utils/Vector.h"

class IKernel {
public:
    virtual double operator()(const Vector &a, const Vector &b) const = 0;
};

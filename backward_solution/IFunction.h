#pragma once

#include "../utils/Vector.h"

class IFunction {
public:
    virtual double operator()(const Vector &v, bool cache = true) const = 0;
    virtual ~IFunction() {}
};
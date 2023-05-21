#pragma once

#include "IFunction.h"

class Simple2DFunction : public IFunction {
public:
    double operator()(const Vector &v, bool cache = true) const;
};
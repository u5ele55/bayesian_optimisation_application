#pragma once

#include "IFunction.h"

class SimpleFunction : public IFunction {
public:
    double operator()(const Vector &v, bool cache = true) const;
};
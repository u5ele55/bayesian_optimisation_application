#include "SimpleFunction.h"

double SimpleFunction::operator()(const Vector &v, bool cache) const
{
    double x = v[0];
    return (6 * x - 2)*(6 * x - 2) * sin(12 * x - 4);
}
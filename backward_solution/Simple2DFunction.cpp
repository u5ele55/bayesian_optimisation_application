#include "Simple2DFunction.h"

double Simple2DFunction::operator()(const Vector &v, bool cache) const
{
    double x = v[0], y = v[1];
    return ((x-1)*(x-1) + 1)*((y-2)*(y-2) + 2) - 3;
}
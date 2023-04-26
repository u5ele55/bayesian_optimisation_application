#include "Vector.h"

Vector::Vector(int n) 
    : Matrix(n, 1) {}

Vector::Vector(std::initializer_list<double> list) 
    : Matrix(list.size(), 1)
{
    int i = 0;
    for (auto p = list.begin(); p != list.end(); p ++) {
        at(i, 0) = *p;
        i++;
    }
}

double& Vector::operator[](int n)
{
    return at(n, 0);
}

double Vector::operator[](int n) const
{
    return at(n, 0);
}
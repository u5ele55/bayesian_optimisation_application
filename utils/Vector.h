#pragma once

#include "Matrix.h"

class Vector : public Matrix {
public:
    Vector(int n);
    Vector(std::initializer_list<double> list);

    double &operator[](int n);
    double operator[](int n) const;

    using Matrix::operator+=;
    using Matrix::operator=;
};
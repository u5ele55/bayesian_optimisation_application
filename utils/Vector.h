#pragma once

#include "Matrix.h"

class Vector : public Matrix {
public:
    Vector(int n);
    Vector(std::initializer_list<double> list);
    Vector(const Matrix &matrix, int column);

    double &operator[](int n);
    double operator[](int n) const;
    explicit operator bool() const;

    using Matrix::operator+=;
    using Matrix::operator=;
};
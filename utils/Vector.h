#pragma once

#include "Matrix.h"

class Vector : public Matrix {
public:
    Vector(int n);

    Vector(std::initializer_list<double> list);

    Vector(std::vector<double> l);

    Vector(const Matrix &matrix, int column);

    double &operator[](int n);

    double operator[](int n) const;

    explicit operator bool() const;


    Vector operator+(const Vector &other) const;

    Vector operator-() const;

    Vector operator-(const Vector &other) const;

    Vector operator*(double val) const;

    Vector &operator+=(const Vector &other);

    Vector &operator=(const Vector &other);

    double dot(const Vector &other);
};
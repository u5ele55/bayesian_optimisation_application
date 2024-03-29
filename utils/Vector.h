#pragma once

#include <Eigen/Core>

#include "Matrix.h"

class Vector : public Matrix {
public:
    Vector(int n);

    Vector(std::initializer_list<double> list);

    Vector(std::vector<double> l);

    Vector(const Vector &other);
    Vector(Vector &&other);

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

    Vector &operator=(const Eigen::VectorXd &other);

    Vector &operator=(Vector &&other);

    bool operator==(const Vector &other) const;

    /**
     * @return is current vector lower then other lexicographically
     * */
    bool operator<(const Vector &other) const;

    /**
     * @return dot product of the vectors
     * */
    double dot(const Vector &other) const;
};
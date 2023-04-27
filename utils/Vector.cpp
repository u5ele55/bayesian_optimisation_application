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

Vector::Vector(const Matrix &matrix, int column)
    : Matrix(matrix.getShape().first, 1)
{
    if (matrix.getShape().second <= column) {
        throw std::invalid_argument("Invalid column number!");
    }
    
    for(int i = 0; i < matrix.getShape().second; i ++) {
        data[i][0] = matrix.at(i, column);
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

Vector::operator bool() const {
    return n;
}

double Vector::dot(const Vector &other) {
    return (this->transpose() * other).at(0,0);
}

Vector Vector::operator-(const Vector &other) const {
    return *this + (-other);
}

Vector Vector::operator*(double val) const
{
    Vector res(n);
    for(int i = 0; i < n; i++) {
        res[i] = data[i][0] * val;
    }
    return res;
}

Vector Vector::operator+(const Vector &other) const {
    if (n != other.n) {
        throw std::invalid_argument("Matrix::operator+: Wrong sizes");
    }
    Vector result = Vector(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            result.at(i, j) = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

Vector Vector::operator-() const {
    Vector result = Vector(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.at(i, j) = -data[i][j];
        }
    }

    return result;
}

Vector &Vector::operator+=(const Vector &other) {
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Vector::operator+=: Wrong sizes");
    }

    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            data[i][j] += other.data[i][j];
        }
    }

    return *this;
}

Vector &Vector::operator=(const Vector &other) {
    resize(other.n, other.m);
    for(int i = 0; i < other.n; i ++) {
        for(int j = 0; j < other.m; j ++) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int n, int m) : n(n), m(m)
{
    this->data = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
}

double& Matrix::at(int y, int x)
{
    return this->data[y][x];
}

double Matrix::at(int y, int x) const
{
    return this->data[y][x];
}

Matrix Matrix::operator*(const double val) const
{
    Matrix other = Matrix(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            other.data[i][j] = data[i][j] * val;
        }
    }
    return other;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (m != other.n) {
        throw std::invalid_argument("Sizes!!!!!!");
    }
    Matrix result = Matrix(n, other.m);
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            for (int k = 0; k < m; k++) {
                result.at(i, j) += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Sizes!!!!!!");
    }
    Matrix result = Matrix(n, other.m);
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            result.at(i, j) = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator-() const
{
    Matrix result = Matrix(n, m);
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.at(i, j) = -data[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    return *this + (-other);
}

Matrix Matrix::transpose() const
{
    Matrix result = Matrix(m,n);

    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            result.data[j][i] = data[i][j];
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix)
{
    stream << "[\n";
    for (int i = 0; i < matrix.n; i ++) {
        stream << " [";
        for (int j = 0; j < matrix.m; j ++) {
            stream << matrix.data[i][j] << ((j == matrix.m-1) ? "" : " ");
        }
        stream << "]\n";
    }
    stream << "]";

    return stream;
}

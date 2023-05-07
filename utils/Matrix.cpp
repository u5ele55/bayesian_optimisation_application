#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int n, int m) : n(n), m(m) {
    this->data = new double[n * m];
}

Matrix::Matrix(const Matrix &other) : n(other.n), m(other.m) {
    this->data = new double[n * m];
    for (int i = 0; i < other.n; i++) {
        for (int j = 0; j < other.m; j++) {
            at(i, j) = other.at(i, j);
        }
    }
}

Matrix::Matrix(Matrix &&other) : n(other.n), m(other.m) {
    this->data = new double[n * m];
    for (int i = 0; i < other.n; i++) {
        for (int j = 0; j < other.m; j++) {
            at(i, j) = other.at(i, j);
        }
    }
}

Matrix::~Matrix() {
    delete [] data;
}

double &Matrix::at(int y, int x) {
    return this->data[y*m + x];
}

double Matrix::at(int y, int x) const {
    return this->data[y*m + x];
}

void Matrix::resize(int n, int m) {
    // TODO: optimize later
    double * newData = new double[n * m];
    for(int i = 0; i < this->n; i ++) {
        for(int j = 0; j < this->m; j ++) {
            newData[i * m + j] = at(i,j);
        }
    }
    
    delete [] data;
    data = newData;

    this->n = n;
    this->m = m;
}

void Matrix::emplaceColumn(const Matrix &column, int index) {
    if (column.getShape().first != n || index >= m) {
        throw std::invalid_argument("Matrix::emplaceColumn: Wrong sizes");
    }
    if (column.getShape().second != 1) {
        throw std::invalid_argument("Matrix::emplaceColumn: column must be a vector!");
    }
    for (int i = 0; i < n; i++) {
        at(i, index) = column.at(i, 0);
    }
}

std::pair<int, int> Matrix::getShape() const {
    return {n, m};
}

Matrix Matrix::operator*(const double val) const {
    Matrix other = Matrix(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            other.at(i, j) = at(i, j) * val;
        }
    }
    return other;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (m != other.n) {
        throw std::invalid_argument("Matrix::emplaceColumn: Wrong sizes");
    }
    Matrix result = Matrix(n, other.m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            for (int k = 0; k < m; k++) {
                result.at(i, j) += at(i, k) * other.at(k, j);
            }
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &other) const {
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Matrix::operator+: Wrong sizes");
    }
    Matrix result = Matrix(n, other.m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            result.at(i, j) = at(i, j) + other.at(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator-() const {
    Matrix result = Matrix(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.at(i, j) = -at(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    return *this + (-other);
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Matrix::operator+=: Wrong sizes");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            at(i, j) += other.at(i, j);
        }
    }

    return *this;
}

Matrix &Matrix::operator=(const Matrix &other) {
    resize(other.n, other.m);
    for (int i = 0; i < other.n; i++) {
        for (int j = 0; j < other.m; j++) {
            at(i, j) = other.at(i, j);
        }
    }
    n = other.n;
    m = other.m;
    return *this;
}

Matrix &Matrix::operator=(Matrix &&other)
{
    resize(other.n, other.m);
    for (int i = 0; i < other.n; i++) {
        for (int j = 0; j < other.m; j++) {
            at(i, j) = other.at(i, j);
        }
    }
    n = other.n;
    m = other.m;
    return *this;
}

Matrix Matrix::transpose() const {
    Matrix result = Matrix(m, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.at(j, i) = at(i, j);
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
    stream << "[\n";
    for (int i = 0; i < matrix.n; i++) {
        stream << " [";
        for (int j = 0; j < matrix.m; j++) {
            stream << matrix.at(i, j) << ((j == matrix.m - 1) ? "" : " ");
        }
        stream << "]\n";
    }
    stream << "]";

    return stream;
}

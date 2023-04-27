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

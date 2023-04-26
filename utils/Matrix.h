#pragma once

#include <vector>
#include <stdexcept>
#include <ostream>

class Matrix {
public:
    Matrix(int n, int m);
    double& at(int y, int x);
    double at(int y, int x) const;

    Matrix transpose() const;

    Matrix operator*(const double val) const;
    Matrix operator*(const Matrix &other) const;

    Matrix operator+(const Matrix &other) const;
    Matrix operator-() const;
    Matrix operator-(const Matrix &other) const;

    friend std::ostream& operator<<(std::ostream &stream, const Matrix &matrix);
private:
    std::vector<std::vector<double>> data;
    int n;
    int m;
};

std::ostream& operator<<(std::ostream &stream, const Matrix &matrix);
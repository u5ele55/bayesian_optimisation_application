#pragma once

#include <vector>
#include <stdexcept>
#include <ostream>

class Matrix {
public:
    explicit Matrix(int n, int m);

    double &at(int y, int x);

    double at(int y, int x) const;

    void resize(int n, int m);

    /**
     * Puts `column` at matrix `index` column
     * */
    void emplaceColumn(const Matrix &column, int index);

    std::pair<int, int> getShape() const;

    Matrix transpose() const;

    Matrix operator*(double val) const;

    Matrix operator*(const Matrix &other) const;

    Matrix operator+(const Matrix &other) const;

    Matrix operator-() const;

    Matrix operator-(const Matrix &other) const;

    Matrix &operator+=(const Matrix &other);

    Matrix &operator=(const Matrix &other);

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);

protected:
    std::vector<std::vector<double>> data;
    int n;
    int m;
};

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);
#pragma once

#include <vector>
#include <stdexcept>
#include <ostream>

class Matrix {
public:
    explicit Matrix(int n, int m);

    Matrix(const Matrix &other);

    Matrix(Matrix &&other);

    ~Matrix();

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

    Matrix &operator=(Matrix &&other);

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);
protected:
    double * data;
    int n;
    int allocatedN;
    int m;
    int allocatedM;
};

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);
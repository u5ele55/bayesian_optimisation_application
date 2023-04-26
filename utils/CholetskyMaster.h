#pragma once

#include "Vector.h"

class CholeskyMaster {
public:
    /// @brief Choletsky decomposition of matrix A 
    static Matrix choleskyDecomposition(const Matrix& A);

    /// @brief if L * L.T = A and newA is A with new column and row, we can use L 
    /// to perform Cholesky decomposition of newA using values of L 
    /// @param newA Matrix with size (n+1)x(n+1) 
    /// @param L Matrix with size n x n, cholesky decomposition of A
    static void choleskyDecompositionIterative(const Matrix& newA, Matrix& L);

    /// @brief Solves L * L.T * x = b 
    static Vector solveCholesky(const Matrix& L, const Vector& b);

    /// @brief Solves L * L.T * X = B and writes answer into `answer` matrix
    static void solveCholesky(const Matrix& L, const Matrix& B, Matrix& answer);
};
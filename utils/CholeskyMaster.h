#pragma once

#include "Vector.h"

class CholeskyMaster {
public:
    /**
     * @param A matrix to decompose
     * @return Cholesky decomposition (L: A = L*L.T)
     * */
    static Matrix choleskyDecomposition(const Matrix &A);

    /**
     * If L * L.T = A and newA is A with new column and row, we can use L
     * to perform Cholesky decomposition of newA using values of L
     * @param newA Matrix with size (n+1)x(n+1)
     * @param L Matrix with size n x n, cholesky decomposition of A
     * */
    static void choleskyDecompositionIterative(const Matrix &newA, Matrix &L);

    /**
     * Solves L * L.T * x = b
     * @return x
     * */
    static Vector solveCholesky(const Matrix &L, const Vector &b);

    /**
     * Solves L * L.T * X = B (X, B - matrices)
     * @param answer X (where to write the answer)
     * */
    static void solveCholesky(const Matrix &L, const Matrix &B, Matrix &answer);
};
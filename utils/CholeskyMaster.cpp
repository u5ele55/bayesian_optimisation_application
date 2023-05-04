#include "CholeskyMaster.h"
#include <iostream>
#include <math.h>

Matrix CholeskyMaster::choleskyDecomposition(const Matrix &A)
{
    if (A.getShape().first != A.getShape().second) {
        throw std::invalid_argument("CholeskyMaster::choleskyDecomposition: Wrong sizes");
    }
    int n = A.getShape().first;
    auto ans = Matrix(n, n);
    // std::cout << "matrix = " << A << "\n";
    // exit(0);
    for (int i = 0; i < n; i ++) {
        for (int k = 0; k < i+1; k ++) {
            double sum = 0;
            for (int j = 0; j < k; j ++) {
                sum = std::fma(ans.at(i, j), ans.at(k, j), sum);
            }
            if (i == k) {
                ans.at(i, k) = sqrtl(A.at(i,i) - sum);
            } else {
                ans.at(i, k) = (A.at(i,k) - sum) / ans.at(k, k);
            }
        }
    }
    // std::cout << "L = " << ans << "\n";
    // exit(0);
    return ans;
}

void CholeskyMaster::choleskyDecompositionIterative(const Matrix &newA, Matrix &L)
{
    if (newA.getShape().first != newA.getShape().second || L.getShape().first + 1 != newA.getShape().first) {
        throw std::invalid_argument("CholeskyMaster::choleskyDecompositionIterative: Wrong sizes");
    }
    int n = L.getShape().first;
    L.resize(n+1, n+1);
    
    // just last row
    for (int k = 0; k < n+1; k ++) {
        double sum = 0;
        for (int i = 0; i < k; i ++) {
            sum += L.at(n, i) * L.at(k, i);
        }
        if (k == n) {
            // L(n+1)(n+1)
            L.at(n, n) = sqrt(newA.at(n, k) - sum);
        } else {
            L.at(n, k) = (newA.at(n, k) - sum) / L.at(k, k);
        }
    }
    
}

Vector CholeskyMaster::solveCholesky(const Matrix &L, const Vector &b)
{
    int n = L.getShape().first;
    if (n != b.getShape().first) {
        throw std::invalid_argument("CholeskyMaster::solveCholesky(Vector): Wrong sizes");
    }
    auto y = Vector(n);

    for (int i = 0; i < n; i ++) {
        double sum = 0;
        for (int j = 0; j < i; j ++) {
            sum = std::fma(y[j], L.at(i, j), sum);
        }
        y[i] = (b[i] - sum) / L.at(i, i);
    }
    
    auto answer = Vector(n);
    for (int i = n - 1; i >= 0; i --) {
        double sum = 0;
        for (int j = i+1; j < n; j ++) {
            sum += answer[j] * L.at(j, i);
        }
        answer[i] = (y[i] - sum) / L.at(i, i);
    }

    return answer;
}

void CholeskyMaster::solveCholesky(const Matrix &L, const Matrix &B, Matrix &answer)
{
    if (   L.getShape().first != B.getShape().first 
        || L.getShape().first != answer.getShape().first 
        || answer.getShape().second != B.getShape().second) 
    {
            throw std::invalid_argument("CholeskyMaster::solveCholesky(Matrix): Wrong sizes");
    }
    
    for (int i = 0; i < B.getShape().second; i ++) {
        Vector b = Vector(B, i);
        answer.emplaceColumn(solveCholesky(L, b), i);
    }
}

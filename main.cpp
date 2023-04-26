#include <iostream>

#include "utils/Vector.h"
#include "forward_problem/system.h"

#include "forward_problem/RK4Solver.h"
#include "forward_problem/system.h"

#include "utils/CholeskyMaster.h"

int main() {
    System system(1, 0.5, 0, 1);

    RK4ForwardSolver solver(system);
    std::cout << solver.getState(10) << '\n';

    Matrix a(2,2);
    a.at(0,0) = 2;
    a.at(0,1) = 3;
    a.at(1,0) = 3;
    a.at(1,1) = 5;

    auto L = CholeskyMaster::choleskyDecomposition(a);
    auto B = Matrix(2,2);
    B.emplaceColumn(Vector{1, 2}, 0);
    B.emplaceColumn(Vector{3, 4}, 1);

    auto x = Matrix(2,2);
    CholeskyMaster::solveCholesky(L, B, x);

    // Test iterative

    a.resize(3,3);
    a.at(2, 0) = 1;
    a.at(2, 1) = 2;
    a.emplaceColumn(Vector{1,2,3}, 2);

    CholeskyMaster::choleskyDecompositionIterative(a, L);

    std::cout << L << '\n';
    std::cout << L * L.transpose() << '\n';
    
    return 0;
}
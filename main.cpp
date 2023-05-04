#include <iostream>

#include "utils/Vector.h"
#include "forward_problem/System.h"

#include "forward_problem/RK4Solver.h"
#include "LinearSpace.h"
#include "utils/CholeskyMaster.h"

#include "backward_solution/GaussianProcesses.h"
#include "backward_solution/BayesianOptimizer.h"
#include "kernel/SquaredExponentialKernel.h"
#include "backward_solution/PendulumMSE.h"

#include <cmath>

int main() {
    System initial(1, 0.5, 0, 0.8);
    RK4ForwardSolver solver(initial);
    LinearSpace space{};
    space.addBoundary({0, 1.5, 0.1}); // omega
    space.addBoundary({0, 1, 0.1}); // dissipation coefficient
    space.addBoundary({0, M_PI_2, 0.2}); // initial angle
    space.addBoundary({0, 1, 0.2}); // initial angular speed

    std::vector<Vector> X = {
            {0, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0},
            {0, 1, 0, 0},
            {1, 0, 0, 0},
    };


    auto y = std::vector<double>(X.size());
    PendulumMSE mse(solver, 50);
    for (int i = 0; i < y.size(); i++) {
        y[i] = mse(X[i]);
    }
    auto *kernel = new SquaredExponentialKernel();
    // std::cout << space.size() << "\n";
    // exit(0);
    GaussianProcesses gp(X, y, space, kernel);

    BayesianOptimizer bo(mse, gp);
    for (int i = 0; i < 10; i++) {
        std::cout << "Step " << i << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;
    }
    delete kernel;
    return 0;
}

int maina() {
    LinearSpace space{};
    space.addBoundary({-2, 10, 0.2});
    std::cout << space.size() << '\n';
    std::vector<Vector> X = {
            {2.99632095},
            {7.60571445},
            {5.85595153},
            {4.78926787},
            {1.24814912},
            {1.24795616},
            {0.4646689},
            {6.92940917}
    };
    auto y = std::vector<double>(X.size());
    for (int i = 0; i < y.size(); i++) {
        y[i] = exp(-X[i][0] / 5.0) * 2 * sin(2 * X[i][0]);

    }
    auto *kernel = new SquaredExponentialKernel();
    GaussianProcesses gp(X, y, space, kernel);

    auto p = gp.predict();
    // std::cout << "im here\n";

    auto mean = p.first;

    std::cout << p.second;

    delete kernel;
    return 0;
}

int mains() {
    System system(1, 0.5, 0, 1);

    RK4ForwardSolver solver(system);
    std::cout << solver.getState(10) << '\n';

    Matrix a(2, 2);
    a.at(0, 0) = 2;
    a.at(0, 1) = 3;
    a.at(1, 0) = 3;
    a.at(1, 1) = 5;

    auto L = CholeskyMaster::choleskyDecomposition(a);
    auto B = Matrix(2, 2);
    B.emplaceColumn(Vector{1, 2}, 0);
    B.emplaceColumn(Vector{3, 4}, 1);

    auto x = Matrix(2, 2);
    CholeskyMaster::solveCholesky(L, B, x);

    // Test iterative

    a.resize(3, 3);
    a.at(2, 0) = 1;
    a.at(2, 1) = 2;
    a.emplaceColumn(Vector{1, 2, 3}, 2);

    CholeskyMaster::choleskyDecompositionIterative(a, L);

    std::cout << L << '\n';
    std::cout << L * L.transpose() << '\n';

    return 0;
}
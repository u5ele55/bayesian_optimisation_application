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
    System initial(0.9, 0.5, 0.4, 0.8);
    RK4ForwardSolver solver(initial);
    LinearSpace space{};
    space.addBoundary({0.5, 1, 0.1}); // omega
    space.addBoundary({0, 1, 0.1}); // dissipation coefficient
    // space.addBoundary({0, M_PI_2, 0.2}); // initial angle
    space.addBoundary({0, 1, 0.1}); // initial angle
    space.addBoundary({0, 1, 0.1}); // initial angular speed

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
    auto *kernel = new SquaredExponentialKernel(5);
    // std::cout << space.size() << "\n";
    // exit(0);
    GaussianProcesses gp(X, y, space, kernel);

    BayesianOptimizer bo(mse, gp);
    for (int i = 0; i < 20; i++) {
        std::cout << "Step " << i << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;
    }
    std::cout << "MIN: \n" << bo.getArgmin() << '\n';

    delete kernel;
    return 0;
}

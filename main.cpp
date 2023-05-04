#include <iostream>
#include <cmath>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "forward_problem/RK4Solver.h"

int main() {
    System initial(0.8, 0.5, 0.4, 0.8);
    RK4ForwardSolver solver(initial);
    LinearSpace space{};
    Dimension omega = {0.2, 0.9, 0.1},
        dissipationCoef = {0.2, 1, 0.1},
        initialAngle = {0, 1, 0.2},
        initialAngularSpeed = {0, 1, 0.2};

    space.addBoundary(omega);
    space.addBoundary(dissipationCoef);
    space.addBoundary(initialAngle);
    space.addBoundary(initialAngularSpeed);

    std::vector<Vector> priorX = {
            {omega.min, dissipationCoef.min, initialAngle.min, initialAngularSpeed.max},
            {omega.min, dissipationCoef.min, initialAngle.max, initialAngularSpeed.min},
            {omega.min, dissipationCoef.max, initialAngle.min, initialAngularSpeed.min},
            {omega.max, dissipationCoef.min, initialAngle.min, initialAngularSpeed.min},
    };


    auto priorY = std::vector<double>(priorX.size());
    PendulumMSE mse(solver, 200);
    for (int i = 0; i < priorY.size(); i++) {
        priorY[i] = mse(priorX[i]);
    }
    auto *kernel = new SquaredExponentialKernel(3);
    GaussianProcesses gp(priorX, priorY, space, kernel);

    BayesianOptimizer bo(mse, gp);
    for (int i = 0; i < 20; i++) {
        std::cout << "Step " << i << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;
    }
    std::cout << "Result point: \n" << bo.getArgmin() << '\n';
    std::cout << "Result MSE: " << mse(bo.getArgmin()) << '\n';

    delete kernel;
    return 0;
}

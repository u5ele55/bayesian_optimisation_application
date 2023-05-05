#include <iostream>
#include <cmath>
#include <fstream>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "utils/SolutionCache.h"

void printSystem(const Vector &state, std::ofstream &output) {
    output << state[0] << " " << state[1] << " " << state[2] << " " << state[3] << "\n";
    auto solution = SolutionCache::getInstance().get(state);
    output << solution.first << " " << solution.second.size() << "\n";
    for (auto it : solution.second) {
        output << it << "\n";
    }
}

int main() {
    System initial{0.5, 0.7, M_PI_2, 1.1};
    double stddev = 0.01;
    RK4SolverWithNoise solver(initial, stddev);

    Dimension omega = {0.2, 1, 0.1},
        dissipationCoef = {0.2, 0.9, 0.1},
        initialAngle = {M_PI_4, M_PI_2, M_PI_4 / 4},
        initialAngularSpeed = {1, 2, 0.1};
    LinearSpace space{};
    space.addBoundary(omega);
    space.addBoundary(dissipationCoef);
    space.addBoundary(initialAngle);
    space.addBoundary(initialAngularSpeed);

    PendulumMSE mse(solver);

    std::ofstream output;
    output.open("../output.txt");
    printSystem(initial.getInitializer(), output); // print data with noise
    mse(initial.getInitializer()); // solve system without noise
    printSystem(initial.getInitializer(), output); // print data without noise

    const int iterationsCount = 50;
    output << iterationsCount << "\n";

    std::vector<Vector> priorX = {
            {omega.min, dissipationCoef.min, initialAngle.min, initialAngularSpeed.max},
            {omega.min, dissipationCoef.min, initialAngle.max, initialAngularSpeed.min},
            {omega.min, dissipationCoef.max, initialAngle.min, initialAngularSpeed.min},
            {omega.max, dissipationCoef.min, initialAngle.min, initialAngularSpeed.min},
    };
    auto priorY = std::vector<double>(priorX.size());
    for (int i = 0; i < priorY.size(); i++) {
        priorY[i] = mse(priorX[i]);
    }
    auto *kernel = new SquaredExponentialKernel(3);
    GaussianProcesses gp(priorX, priorY, space, kernel, stddev);

    BayesianOptimizer bo(mse, gp);
    for (int i = 0; i < iterationsCount; i++) {
        std::cout << "Step " << i << " started\n";
        auto prediction = bo.step();
        std::cout << i << ": " << prediction << std::endl;
        printSystem(prediction, output);
    }
    auto argmin = bo.getArgmin();
    printSystem(argmin, output);
    std::cout << "Result point: \n" << argmin << '\n';
    std::cout << "Result MSE: " << mse(bo.getArgmin()) << '\n';

    delete kernel;
    output.close();
    return 0;
}

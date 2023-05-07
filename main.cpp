#include <iostream>
#include <cmath>
#include <fstream>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "utils/SolutionCache.h"

void printSystem(std::ofstream &output, const std::vector<double>& values) {
    // output << state[0] << " " << state[1] << " " << state[2] << " " << state[3] << "\n";
    // auto solution = SolutionCache::getInstance().get(state);
    output << values.size() << "\n";
    for (auto it : values) {
        output << it << "\n";
    }
}

int main() {
    System initial{0.9, 0.4, M_PI_2, 0.4};
    double stddev = 0.05;
    RK4SolverWithNoise solver(initial, stddev);

    Dimension omega = {0.2, 1, 0.1},
        dissipationCoef = {0.2, 0.9, 0.1},
        initialAngle = {M_PI_4, M_PI_2, M_PI_4 / 4},
        initialAngularSpeed = {0, 1, 0.1};
    LinearSpace space{};
    space.addBoundary(omega);
    space.addBoundary(dissipationCoef);
    space.addBoundary(initialAngle);
    space.addBoundary(initialAngularSpeed);

    PendulumMSE mse(solver);
    std::ofstream output;
    output.open("../output.txt");

    double mseStep = mse.getStep();
    output << mseStep << "\n";
    printSystem(output, mse.getTrueValues()); // print data with noise
    mse(initial.getInitializer()); // solve system without noise
    auto initialValues = SolutionCache::getInstance().get(initial.getInitializer());
    printSystem(output, initialValues); // print data without noise

    const int iterationsCount = 30;
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
        printSystem(output, SolutionCache::getInstance().get(prediction));
    }
    auto argmin = bo.getArgmin();
    printSystem(output, SolutionCache::getInstance().get(argmin));
    std::cout << "Result point: \n" << argmin << '\n';
    std::cout << "Result MSE: " << mse(bo.getArgmin()) << '\n';

    delete kernel;
    output.close();
    return 0;
}

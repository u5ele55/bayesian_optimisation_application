#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <LBFGS.h>

#include "backward_solution/BayesianOptimizer.h"
#include "functions/PendulumMSE.h"
#include "functions/SimpleFunction.h"
#include "functions/Simple2DFunction.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "backward_solution/kernel/Matern52Kernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "utils/SolutionCache.h"
#include "utils/logs/FileLogger.h"
#include "backward_solution/acquisition/AcquisitionUCB.h"
#include "backward_solution/acquisition/AcquisitionEI.h"
#include "SystemFixedDissipationFabric.h"
#include "SystemOnlyAngleFabric.h"
#include "forward_problem/SystemAngleAndSpeedFabric.h"
#include "forward_problem/FullSystemFabric.h"

int test2d();

int main() {
    Vector initialParams(4);
    std::cout << "Enter initial parameters (omega, dissipation, angle, angular speed): ";
    std::cin >> initialParams[0] >> initialParams[1] >> initialParams[2] >> initialParams[3];
    // Vector initialParams(1);
    // std::cout << "Enter initial angle: ";
    // std::cin >> initialParams[0];
    // Vector initialParams(2);
    // std::cout << "Enter initial angle and angular speed: ";
    // std::cin >> initialParams[0] >> initialParams[1];

    // const double dissipationCoefficient = 0.9,
    //     omega = 0.9,
    //     angularSpeed = 0.9;


    // auto *fabric = new SystemFixedDissipationFabric(dissipationCoefficient);
    auto *fabric = new FullSystemFabric;
    // auto *fabric = new SystemOnlyAngleFabric(dissipationCoefficient, omega, angularSpeed);
    // auto *fabric = new SystemAngleAndSpeedFabric(dissipationCoefficient, omega);
    System initial = fabric->produce(initialParams);

    double stddev = 0.01;
    RK4SolverWithNoise solver(initial, stddev, 42);

    Boundary initialOmega = {0.5, 1.5},
        initialDissip = {0.05, 1.5},
        initialAngle = {-M_PI_2, M_PI_2},
        initialAngularSpeed = {-1.5, 1.5};

    PendulumMSE mse(solver, stddev, fabric);
    AbstractLogger *output = new FileLogger("../test.txt");
    double mseStep = mse.getStep();
    output->stream() << mseStep << "\n";
    output->printSystem(mse.getTrueValues()); // print data with noise
    mse(initialParams); // solve system without noise
    auto initialValues = SolutionCache::getInstance().get(initialParams);
    output->printSystem(initialValues); // print data without noise

    auto bndWCoef = [](Boundary b, double coef) -> double {
        return coef * b.min + (1 - coef) * b.max;
    };

    
    // Generating prior data uniformly
    double parts = 2;
    int priorCount = pow(parts, initialParams.getShape().first);
    std::vector<Vector> priorX;
    std::vector<double> priorY;
    priorX.reserve(priorCount);
    priorY.reserve(priorCount);
    for (int i = 0; i < priorCount; i++) {
        auto params = std::vector<double>(initialParams.getShape().first);
        for (int j = 0; j < initialParams.getShape().first; j++) {
            params[j] = 1 / (parts + 1) * (((i >> j) & 1) + 1);
        }
        priorX.push_back({
                                 bndWCoef(initialOmega, params[0]),
                                 bndWCoef(initialDissip, params[1]),
                                 bndWCoef(initialAngle, params[2]),
                                 bndWCoef(initialAngularSpeed, params[3]),
                         });
        priorY.push_back(mse(priorX[i]));
    }

    // auto *kernel = new SquaredExponentialKernel(1, 0.5);
    auto *kernel = new Matern52Kernel(2, 0.5);
    int acqChoice;
    std::cout << "ACQ: 0 - UCB, !0 - EI\n";
    std::cin >> acqChoice;
    IAcquisition *acq;
    if (acqChoice) {
        acq = new AcquisitionEI;
    } else {
        acq = new AcquisitionUCB(4);
    }
    GaussianProcesses gp(priorX, priorY, kernel, stddev);
    auto bo = BayesianOptimizer(mse, gp, {initialOmega, initialDissip, initialAngle, initialAngularSpeed}, acq, 42, 50);
    // auto bo = BayesianOptimizer(mse, gp, {initialAngle}, acq, 42, 10);
    // auto bo = BayesianOptimizer(mse, gp, {initialAngle, initialAngularSpeed}, acq, 42, 50);
// 1.23 0.987 -1 0 200
// 1 1.57 -1.5 0 100
// 1 0.987 -1.3 1 300

// 0.8 1.25 -1.5 0 200
    int iterations;
    std::cout << "Enter quantity of BO iterations to perform: ";
    std::cin >> iterations;

    for (int i = 0; i < iterations; i++) {
        auto res = bo.step();
        std::cout << "At iteration " << i << " checked position with MSE " << res.second << ": " << res.first << '\n';
        output->printSystem(SolutionCache::getInstance().get(res.first));
    }

    auto argmin = bo.getArgmin();
    std::cout << "AAAND our winner is.. " << mse(argmin) << " - " << argmin << " !!!! \n";
    output->printSystem(SolutionCache::getInstance().get(argmin));

    // std::cout << gp.predict({{0.1}}).first << ' ' << gp.predict({{0.1}}).second << '\n';
    // std::cout << gp.predict({{0.25}}).first << ' ' << gp.predict({{0.25}}).second << '\n';
    // std::cout << gp.predict({{0.9}}).first << ' ' << gp.predict({{0.9}}).second << '\n';
    //

    delete kernel;
    delete acq;
    delete output;
    delete fabric;

    return 0;
}


int test2d() {
    Boundary regionX = {0, 5}, regionY = {0, 5};
    Simple2DFunction f;
    std::vector<Vector> priorX = {
            {1, 1},
            {1, 0.5},
            {4, 3}
    };
    auto priorY = std::vector<double>(priorX.size());
    for (int i = 0; i < priorY.size(); i++) {
        priorY[i] = f(priorX[i]);
    }

    auto *kernel = new SquaredExponentialKernel(1, 1);
    int acqChoice;
    std::cout << "ACQ: 0 - UCB, !0 - EI\n";
    std::cin >> acqChoice;
    IAcquisition *acq;
    if (acqChoice) {
        acq = new AcquisitionEI;
    } else {
        acq = new AcquisitionUCB(2);
    }

    GaussianProcesses gp(priorX, priorY, kernel, 0);
    auto bo = BayesianOptimizer(f, gp, {regionX, regionY}, acq, 10);

    for (int i = 0;; i++) {
        int c;
        std::cout << "Enter non-zero to make step: ";
        std::cin >> c;
        if (c) {
            auto res = bo.step();
            std::cout << "At iteration " << i << " checked position with value " << res.second << ": " << res.first
                      << '\n';
        } else {
            break;
        }
    }

    auto argmin = bo.getArgmin();
    std::cout << "AAAND our winner is.. " << f(argmin) << " - " << argmin << " !!!! \n";

    delete kernel;
    delete acq;
    return 0;
}
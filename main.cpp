#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <LBFGS.h>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/PendulumMSE.h"
#include "backward_solution/SimpleFunction.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "backward_solution/kernel/Matern52Kernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "utils/SolutionCache.h"
#include "utils/logs/FileLogger.h"
#include "backward_solution/acquisition/AcquisitionUCB.h"
#include "backward_solution/acquisition/AcquisitionEI.h"

int main() {
    double initOmega, initDiss, initAngle, initSpeed;
    std::cout << "Enter initial parameters (omega, dissipation, angle, angular speed): ";
    std::cin >> initOmega >> initDiss >> initAngle >> initSpeed;

    System initial{initOmega, initDiss, initAngle, initSpeed};
    
    double stddev = 0.03;
    RK4SolverWithNoise solver(initial, stddev);

    Boundary omega = {0.5, 1.5},
        dissipationCoef = {0.1, 1},
        initialAngle = {-M_PI_2, M_PI_2},
        initialAngularSpeed = {-1.5, 1.5};
    
    PendulumMSE mse(solver, stddev);
    AbstractLogger *output = new FileLogger("../test.txt");
// 0.85 0.6234 0.9813 0.674
// 0.85 0.2234 0.9813 1.474
//  1.25 0.1234 0.9813 1.474 
// 1 0.9
    double mseStep = mse.getStep();
    output->stream() << mseStep << "\n";
    output->printSystem(mse.getTrueValues()); // print data with noise
    mse(initial.getInitializer()); // solve system without noise
    auto initialValues = SolutionCache::getInstance().get(initial.getInitializer());
    output->printSystem(initialValues); // print data without noise

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
    
    auto *kernel = new SquaredExponentialKernel(1, 0.9);
    int acqChoice; std::cout << "ACQ: 0 - UCB, !0 - EI\n"; std::cin >> acqChoice;
    IAcquisition *acq;
    if (acqChoice) {
        acq = new AcquisitionEI;
    } else {
        acq = new AcquisitionUCB(2);
    }

    GaussianProcesses gp(priorX, priorY, kernel, stddev);
    auto bo = BayesianOptimizer(mse, gp, {omega, dissipationCoef, initialAngle, initialAngularSpeed}, acq, 50);

    int iterations;
    std::cout << "Enter quantity of BO iterations to perform: ";
    std::cin >> iterations;

    for (int i = 0; i < iterations; i ++) {
        auto res = bo.step();
        std::cout << "At iteration " << i << " checked position with MSE " << res.second << ": " << res.first << '\n';
        output->printSystem(SolutionCache::getInstance().get(res.first));
    }

    auto argmin = bo.getArgmin();
    std::cout << "AAAND our winner is.. " << mse(argmin) << " - " << argmin << " !!!! \n";
    output->printSystem(SolutionCache::getInstance().get(argmin));

    delete kernel;
    delete acq;
    delete output;
    
    return 0;
}

int test1d() {
    Boundary region = {0, 1};
    SimpleFunction f;
    std::vector<Vector> priorX = {
            {0.1}
    };
    auto priorY = std::vector<double>(priorX.size());
    for (int i = 0; i < priorY.size(); i++) {
        priorY[i] = f(priorX[i]);
    }
    
    auto *kernel = new SquaredExponentialKernel(1, 0.1);
    int acqChoice; std::cout << "ACQ: 0 - UCB, !0 - EI\n"; std::cin >> acqChoice;
    IAcquisition *acq;
    if (acqChoice) {
        acq = new AcquisitionEI;
    } else {
        acq = new AcquisitionUCB(2);
    }

    GaussianProcesses gp(priorX, priorY, kernel, 0);
    auto bo = BayesianOptimizer(f, gp, {region}, acq, 5);

    for (;;) {
        int c; std::cout << "Enter non-zero to make step: "; std::cin >> c;
        if (c) {
            auto res = bo.step();
            std::cout << "Checked position with value " << res.second << ": " << res.first << '\n';
        } else {
            break;
        }
    }

    auto argmin = bo.getArgmin();
    std::cout << "AAAND our winner is.. " << f(argmin) << " - " << argmin << " !!!! \n";

    delete kernel;
    delete acq;
}
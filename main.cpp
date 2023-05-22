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

#define FIX_DISSIPATION false

int test2d();

int main() {
    double initOmega, initDiss, initAngle, initSpeed;
    std::cout << "Enter initial parameters (omega, dissipation, angle, angular speed): ";
    std::cin >> initOmega >> initDiss >> initAngle >> initSpeed;

    System initial{initOmega, initDiss, initAngle, initSpeed};
    
    double stddev = 0.03;
    RK4SolverWithNoise solver(initial, stddev);

    Boundary omega = {0.5, 2},
        dissipationCoef = {0, 1.5},
        initialAngle = {-M_PI_2, M_PI_2},
        initialAngularSpeed = {-2, 2};

    if (FIX_DISSIPATION) {
        dissipationCoef.min = initDiss - 1e-4;
        dissipationCoef.max = initDiss + 1e-4;
    }

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

    auto bndWCoef = [](Boundary b, double coef) -> double {
        return coef*b.min + (1-coef)*b.max;
    };

    int priorCount = 16;
    std::vector<Vector> priorX;
    std::vector<double> priorY;
    priorX.reserve(priorCount);
    priorY.reserve(priorCount);
    double priorRoot = pow(priorCount, 0.25);
    for (int i = 0; i < priorCount; i++) {
        auto params = std::vector<double>(4);
        for (int j = 0; j < 4; j++) {
            params[j] = 1 / (priorRoot + 1) * (((i >> j) & 1) + 1);
        }
        priorX.push_back({
            bndWCoef(omega, params[0]),
            bndWCoef(dissipationCoef, params[1]),
            bndWCoef(initialAngle, params[2]),
            bndWCoef(initialAngularSpeed, params[3]),
        });
        priorY.push_back(mse(priorX[i]));
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
    std::cout << argmin[0] << " " << argmin[1] << " " << argmin[2] << " " << argmin[3] << "\n";
    output->printSystem(SolutionCache::getInstance().get(argmin));

    delete kernel;
    delete acq;
    delete output;
    
    return 0;
}



int test2d() {
    Boundary regionX = {0, 5}, regionY = {0,5};
    Simple2DFunction f;
    std::vector<Vector> priorX = {
            {1, 1}, {1, 0.5}, {4, 3}
    };
    auto priorY = std::vector<double>(priorX.size());
    for (int i = 0; i < priorY.size(); i++) {
        priorY[i] = f(priorX[i]);
    }
    
    auto *kernel = new SquaredExponentialKernel(1, 1);
    int acqChoice; std::cout << "ACQ: 0 - UCB, !0 - EI\n"; std::cin >> acqChoice;
    IAcquisition *acq;
    if (acqChoice) {
        acq = new AcquisitionEI;
    } else {
        acq = new AcquisitionUCB(2);
    }

    GaussianProcesses gp(priorX, priorY, kernel, 0);
    auto bo = BayesianOptimizer(f, gp, {regionX, regionY}, acq, 10);

    for (int i = 0;; i++) {
        int c; std::cout << "Enter non-zero to make step: "; std::cin >> c;
        if (c) {
            auto res = bo.step();
            std::cout << "At iteration " << i << " checked position with value " << res.second << ": " << res.first << '\n';
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
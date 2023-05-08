#include <iostream>
#include <cmath>
#include <fstream>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "backward_solution/OptimizerEpoch.h"
#include "utils/SolutionCache.h"
#include "utils/logs/FileLogger.h"

const int EPOCH_QUANTITY = 3;

int main() {
    System initial{M_SQRT2, 0.55555555555555555555, -M_PI_2, M_SQRT1_2};
    double stddev = 0.05;
    RK4SolverWithNoise solver(initial, stddev);

    Dimension omega = {0.1, 2, 0.2},
            dissipationCoef = {0.1, 1.5, 0.2},
            initialAngle = {-M_PI_2, M_PI_2, M_PI_4},
            initialAngularSpeed = {0, 2, 0.2};
    LinearSpace space{};
    space.addBoundary(omega);
    space.addBoundary(dissipationCoef);
    space.addBoundary(initialAngle);
    space.addBoundary(initialAngularSpeed);

    PendulumMSE mse(solver);
    AbstractLogger *output = new FileLogger("../test.txt");

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
    auto *kernel = new SquaredExponentialKernel(stddev, 0.5);

    GaussianProcesses gp(priorX, priorY, space, kernel, stddev);
    auto *bo = new BayesianOptimizer(mse, gp);
    auto *epoch = new OptimizerEpoch(*bo, output);
    auto epochMin = epoch->iterate();
    auto minBoundary = Vector({omega.min, dissipationCoef.min, initialAngle.min, initialAngularSpeed.min});
    auto maxBoundary = Vector({omega.max, dissipationCoef.max, initialAngle.max, initialAngularSpeed.max});

    std::cout << "Epoch 0 best: " << epochMin << '\n';
    for (int i = 1; i < EPOCH_QUANTITY; i++) {
        // rebuild space
        LinearSpace newSpace;
        for (int j = 0; j < epochMin.getShape().first; j++) {
            auto oldDim = space.getDimension(j);
            double oldStep = oldDim.step;
            double newStep = 2 * oldStep / ceil((oldDim.max - oldDim.min) / oldStep);
            double newMin = fmax(epochMin[j] - oldStep * 1.5, minBoundary[j]);
            double newMax = fmin(epochMin[j] + oldStep * 1.5, maxBoundary[j]);
            newSpace.addBoundary({newMin, newMax, newStep});
        }
        space = newSpace;
        auto checkedPreviously = bo->getChecked();
        // filter checked points that belong to new space
        std::vector<Vector> newPriorX;
        std::vector<double> newPriorY;
        for (const auto &v: checkedPreviously) {
            bool inSpace = true;
            for (int i = 0; i < v.getShape().first; i++) {
                if (space.getDimension(i).min > v[i] || v[i] > space.getDimension(i).max) {
                    inSpace = false;
                }
            }
            if (inSpace) {
                newPriorX.push_back(v);
                newPriorY.push_back(mse(v));
            }
        }

        // treat them as priorX and priorY
        // create gp and bo on it
        GaussianProcesses newGp(newPriorX, newPriorY, space, kernel, stddev);
        delete bo;
        bo = new BayesianOptimizer(mse, newGp);

        // create epoch for new bo and iterate
        delete epoch;
        epoch = new OptimizerEpoch(*bo, output);

        epochMin = epoch->iterate();
        std::cout << "Epoch " << i << " best: " << epochMin << '\n';
    }


    auto argmin = bo->getArgmin();
    output->printSystem(SolutionCache::getInstance().get(argmin));
    std::cout << "Result point: \n" << argmin << '\n';
    std::cout << "Result MSE: " << mse(bo->getArgmin()) << '\n';

    delete kernel;
    delete bo;
    delete epoch;
    delete output;

    return 0;
}

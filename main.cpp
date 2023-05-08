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
    System initial{0.93, sqrt(2) / 2, M_PI_2, 0.41};
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
    ILogger * output = new FileLogger("../test.txt");
    
    double mseStep = mse.getStep();
    output->stream() << mseStep << "\n";
    printSystem(output->stream(), mse.getTrueValues()); // print data with noise
    mse(initial.getInitializer()); // solve system without noise
    auto initialValues = SolutionCache::getInstance().get(initial.getInitializer());
    printSystem(output->stream(), initialValues); // print data without noise

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
    BayesianOptimizer * bo = new BayesianOptimizer(mse, gp);
    OptimizerEpoch * epoch = new OptimizerEpoch(*bo, output);
    auto epochMin = epoch->iterate();
    std::cout << "Epoch 0 best: " << epochMin << '\n';
    for(int i = 1; i < EPOCH_QUANTITY; i ++) {
        // rebuild space
        LinearSpace newSpace;
        for(int j = 0; j < epochMin.getShape().first; j ++) {
            auto oldDim = space.getDimension(j);
            double oldDimStep = oldDim.step;
            double newStep = 2 * oldDimStep / ceil( (oldDim.max - oldDim.min) / oldDimStep );
            newSpace.addBoundary({epochMin[j] - oldDimStep, epochMin[j] + oldDimStep, newStep});
        }
        space = newSpace;
        auto checkedPreviously = bo->getChecked();
        // filter checked points that belong to new space
        std::vector<Vector> newPriorX;
        std::vector<double> newPriorY;
        for (const auto &v : checkedPreviously) {
            bool inSpace = true;
            for(int i = 0; i < v.getShape().first; i ++) {
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
    printSystem(output->stream(), SolutionCache::getInstance().get(argmin));
    std::cout << "Result point: \n" << argmin << '\n';
    std::cout << "Result MSE: " << mse(bo->getArgmin()) << '\n';

    delete kernel;
    delete bo;
    delete epoch;
    delete output;

    return 0;
}

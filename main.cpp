#include <iostream>
#include <cmath>

#include "backward_solution/BayesianOptimizer.h"
#include "backward_solution/kernel/SquaredExponentialKernel.h"
#include "backward_solution/kernel/Matern52Kernel.h"
#include "forward_problem/RK4SolverWithNoise.h"
#include "utils/SolutionCache.h"
#include "utils/logs/FileLogger.h"

const int EPOCH_QUANTITY = 3;

double someF(Vector x) {
    return x[0] * x[0] + sin(x[0]);
}

int main() {

    std::vector<Vector> priorX = { {0.1}, {0.5}, {1}, {1.1}, {1.5} };
    std::vector<double> priorY;
    for(auto v : priorX) {
        priorY.push_back(someF(v));
    } 

    auto *kernel = new SquaredExponentialKernel(1, 0.5);

    GaussianProcesses gp(priorX, priorY, kernel, 0.0001);

    std::vector<Vector> wantToPredict = {
        {0.2}, {0.4}, {0.8}, {1.1}
    };

    auto ans = gp.predict(wantToPredict);
    auto mean = ans.first;
    auto dev = ans.second;
    for(int i = 0; i < mean.getShape().first; i ++) {
        std::cout << someF(wantToPredict[i]) << " ~ " << mean[i] << " " << dev[i] <<  '\n';
    }
    
    return 0;

}

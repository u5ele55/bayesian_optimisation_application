//
// Created by ormequ on 27.04.23.
//

#pragma once

#include "kernel/IKernel.h"
#include "../utils/Vector.h"
#include "../utils/LinearSpace.h"
#include <vector>

class GaussianProcesses {
public:
    GaussianProcesses(const std::vector<Vector> &priorX, std::vector<double> priorY, LinearSpace &space,
                      IKernel *kernel, double noise = 3e-7);

    void fit(const Vector &newX, double newY);

    /// @brief predicts gaussian distribution
    /// @return pair of mean, covariance matrix
    std::pair<Vector, Matrix> predict();

    LinearSpace &getSpace();

private:
    IKernel *kernel;
    double noise;
    std::vector<Vector> x;
    std::vector<double> y;
    Matrix covarianceMatrix;
    Matrix covarianceChol;
    Matrix aposteriorCovariance;
    Matrix influenceCovariance;
    LinearSpace &space;
};


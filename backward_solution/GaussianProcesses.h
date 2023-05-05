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

    /**
     * Adds newX and newY into gaussian processes for next prediction
     * */
    void fit(const Vector &newX, double newY);

    /**
     * Predicts gaussian distribution
     * @return pair of mean, covariance matrix
     * */
    std::pair<Vector, Matrix> predict();

    LinearSpace &getSpace();

private:
    IKernel *kernel;
    std::vector<Vector> x;
    std::vector<double> y;
    Matrix covarianceMatrix;
    Matrix covarianceChol;
    Matrix aposteriorCovariance;
    Matrix influenceCovariance;
    LinearSpace &space;
};


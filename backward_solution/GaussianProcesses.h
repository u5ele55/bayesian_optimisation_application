//
// Created by ormequ on 27.04.23.
//

#pragma once

#include "kernel/IKernel.h"
#include "../utils/Vector.h"
#include "../utils/Boundaries.h"
#include <vector>

class GaussianProcesses {
public:
    GaussianProcesses(const std::vector<Vector> &priorX, std::vector<double> priorY,
                      IKernel *kernel, double noise = 3e-7);

    /**
     * Adds newX and newY into gaussian processes for next prediction
     * */
    void fit(const std::vector<Vector> &newX, const std::vector<double> &newY);

    /**
     * Predicts gaussian distribution
     * @return pair of mean, covariance matrix
     * */
    std::pair<Vector, Vector> predict(const std::vector<Vector> &X);

    /// @brief recalculates influenceCovariance
    void calculateInfluence(const std::vector<Vector> &X);
    
    double getMinY() const;
    Vector getArgmin() const;
private:
    IKernel *kernel;
    std::vector<Vector> x;
    std::vector<double> y;
    Matrix covarianceMatrix;
    Matrix covarianceChol;
    Matrix aposteriorCovariance;
    Matrix influenceCovariance;
};


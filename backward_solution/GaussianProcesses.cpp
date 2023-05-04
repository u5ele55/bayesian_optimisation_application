//
// Created by ormequ on 27.04.23.
//

#include "GaussianProcesses.h"
#include "../utils/CholeskyMaster.h"
#include <iostream>

GaussianProcesses::GaussianProcesses(const std::vector<Vector> &priorX, std::vector<double> priorY, LinearSpace &space,
                                     IKernel *kernel, double noise)
        : kernel(kernel),
          noise(noise),
          x(priorX),
          y(priorY),
          covarianceMatrix(x.size(), x.size()),
          covarianceChol(x.size(), x.size()),
          space(space),
          aposteriorCovariance(space.size(), space.size()),
          influenceCovariance(space.size(), x.size()) {
    std::cout << "Constructing GP...\n";
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < i + 1; j++) {
            covarianceMatrix.at(i, j) = (*kernel)(x[i], x[j]);
            covarianceMatrix.at(j, i) = covarianceMatrix.at(i, j);
        }
    }

    auto noiseMatrix = Matrix(x.size(), x.size());
    for (int i = 0; i < x.size(); i ++) {
        noiseMatrix.at(i,i) = noise;
    }
    covarianceMatrix = covarianceMatrix + noiseMatrix;

    covarianceChol = CholeskyMaster::choleskyDecomposition(covarianceMatrix);

    auto tempSpace = LinearSpace(space);
    space.clear();
    for (size_t i = 0; i < space.size(); i++) {
        if (i % 1000 == 0) {
            std::cout << "GP posteriorCov created " << i << "/" << space.size() << " rows\n";
        }
        auto a = space.next();
        for (size_t j = 0; j < x.size(); j++) {
            influenceCovariance.at(i, j) = (*kernel)(a, x[j]);
        }
        tempSpace.clear();
        for (size_t j = 0; j < tempSpace.size(); j++) {
            auto b = tempSpace.next();
            aposteriorCovariance.at(i, j) = (*kernel)(a, b);
        }
    }
    std::cout << "GP created!!!!!\n";
}

void GaussianProcesses::fit(const Vector &newX, double newY) {
    x.push_back(newX);
    y.push_back(newY);
    covarianceMatrix.resize(x.size(), x.size());

    int i = x.size() - 1;
    for (int j = 0; j < x.size(); j++) {
        covarianceMatrix.at(i, j) = (*kernel)(x[i], x[j]);
        covarianceMatrix.at(j, i) = covarianceMatrix.at(i, j);
    }
    CholeskyMaster::choleskyDecompositionIterative(covarianceMatrix, covarianceChol);

    space.clear();
    influenceCovariance.resize(space.size(), x.size());
    for (size_t j = 0; j < space.size(); j++) {
        auto a = space.next();
        influenceCovariance.at(j, i) = (*kernel)(a, x[i]);
    }
}

std::pair<Vector, Matrix> GaussianProcesses::predict() {
    auto vy = Vector(y);
    auto covarianceInvertedDataY = CholeskyMaster::solveCholesky(covarianceChol, vy);

    auto mean = Vector(influenceCovariance * covarianceInvertedDataY, 0);

    auto covInvertedTimesInfluence = Matrix(x.size(), influenceCovariance.getShape().first);
    CholeskyMaster::solveCholesky(covarianceChol, influenceCovariance.transpose(), covInvertedTimesInfluence);
    auto conditionalCovariance = aposteriorCovariance - influenceCovariance * covInvertedTimesInfluence;
    return {mean, conditionalCovariance};
}

LinearSpace &GaussianProcesses::getSpace() {
    return space;
}

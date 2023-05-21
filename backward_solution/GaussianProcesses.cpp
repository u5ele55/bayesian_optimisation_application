//
// Created by ormequ on 27.04.23.
//

#include "GaussianProcesses.h"
#include "../utils/CholeskyMaster.h"
#include <iostream>
#include <cmath>

#define START_POSTERIOR_CNT 15

GaussianProcesses::GaussianProcesses(const std::vector<Vector> &priorX, std::vector<double> priorY,
                                     IKernel *kernel, double noise)
        : kernel(kernel),
          x(priorX),
          y(priorY),
          covarianceMatrix(x.size(), x.size()),
          covarianceChol(x.size(), x.size()),
          aposteriorCovariance(START_POSTERIOR_CNT, START_POSTERIOR_CNT),
          influenceCovariance(START_POSTERIOR_CNT, x.size()) {
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < i + 1; j++) {
            covarianceMatrix.at(i, j) = (*kernel)(x[i], x[j]);
            covarianceMatrix.at(j, i) = covarianceMatrix.at(i, j);
        }
    }
    
    for (int i = 0; i < x.size(); i ++) {
        covarianceMatrix.at(i,i) += noise;
    }

    covarianceChol = CholeskyMaster::choleskyDecomposition(covarianceMatrix);
}

void GaussianProcesses::fit(const std::vector<Vector> &newX, const std::vector<double> &newY) {
    for(const auto &vecX : newX) {
        x.push_back(vecX);
    }
    for(const auto &target : newY) {
        y.push_back(target);
    }
    covarianceMatrix.resize(x.size(), x.size());

    int i = x.size() - 1;
    for (int j = 0; j < x.size(); j++) {
        covarianceMatrix.at(i, j) = (*kernel)(x[i], x[j]);
        covarianceMatrix.at(j, i) = covarianceMatrix.at(i, j);
    }
    CholeskyMaster::choleskyDecompositionIterative(covarianceMatrix, covarianceChol);
}

std::pair<Vector, Vector> GaussianProcesses::predict(const std::vector<Vector> &X) {
    auto vy = Vector(y);
    auto covarianceInvertedDataY = CholeskyMaster::solveCholesky(covarianceChol, vy);

    calculateInfluence(X);
    auto mean = Vector(influenceCovariance * covarianceInvertedDataY, 0);
    auto covInvertedTimesInfluence = Matrix(x.size(), influenceCovariance.getShape().first);
    CholeskyMaster::solveCholesky(covarianceChol, influenceCovariance.transpose(), covInvertedTimesInfluence);
    aposteriorCovariance.resize(X.size(), X.size());

    for(int i = 0; i < X.size(); i ++) {
        for(int j = 0; j < X.size(); j ++) {
            aposteriorCovariance.at(i, j) = (*kernel)(X[i], X[j]);
        }
    }
    
    auto variance = Vector(X.size());

    for (int i = 0; i < X.size(); i ++) {
        double prod = 0;

        for (int j = 0; j < X.size(); j ++) {
            prod += influenceCovariance.at(i, j) * covInvertedTimesInfluence.at(j, i);
        }

        variance[i] = sqrt( aposteriorCovariance.at(i,i) - prod );
    }

    return {mean, variance};
}

void GaussianProcesses::calculateInfluence(const std::vector<Vector> &X)
{
    influenceCovariance.resize(X.size(), x.size());
    for (int i = 0; i < X.size(); i ++) {
        for (int j = 0; j < x.size(); j ++) {
            influenceCovariance.at(i, j) = (*kernel)(X[i], x[j]);
        }
    }
}

double GaussianProcesses::getMinY() const
{
    double mY = y[0];
    for(int i = 1; i < y.size(); i ++) {
        if (mY > y[i]) {
            mY = y[i];
        }
    }
    return mY;
}

Vector GaussianProcesses::getArgmin() const
{
    double mY = y[0];
    Vector argmin(x[0]);
    for(int i = 1; i < y.size(); i ++) {
        if (mY > y[i]) {
            mY = y[i];
            argmin = x[i];
        }
    }
    return argmin;
}

//
// Created by ormequ on 24.05.23.
//

#pragma once

#include "ISystemFabric.h"

class SystemOnlyAngleFabric : public ISystemFabric {
public:
    SystemOnlyAngleFabric(double dissipation, double omega, double angularSpeed);

    System produce(const Vector &params) override;

    ~SystemOnlyAngleFabric() override = default;

private:
    double dissipation;
    double omega;
    double angularSpeed;
};

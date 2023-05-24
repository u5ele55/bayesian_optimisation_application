//
// Created by ormequ on 24.05.23.
//

#pragma once

#include "ISystemFabric.h"

class SystemAngleAndSpeedFabric : public ISystemFabric {
public:
    System produce(const Vector &params) override;

    ~SystemAngleAndSpeedFabric() override = default;
private:
    double dissipation;
public:
    SystemAngleAndSpeedFabric(double dissipation, double omega);

private:
    double omega;
};

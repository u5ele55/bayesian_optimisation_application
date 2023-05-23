//
// Created by ormequ on 23.05.23.
//

#pragma once

#include "System.h"
#include "ISystemFabric.h"

class SystemFixedDissipationFabric : public ISystemFabric {
public:
    explicit SystemFixedDissipationFabric(double dissipation);

    System produce(const Vector& params);

    ~SystemFixedDissipationFabric() override = default;
private:
    double dissipation;
};

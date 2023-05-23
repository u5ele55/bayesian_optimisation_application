//
// Created by ormequ on 23.05.23.
//
#pragma once

#include "System.h"

class ISystemFabric {
public:
    virtual System produce(const Vector &params) = 0;

    virtual ~ISystemFabric() = default;
};


#pragma once

#include "ISystemFabric.h"

class FullSystemFabric : public ISystemFabric {
public:
    System produce(const Vector &params);

    ~FullSystemFabric() = default;
};
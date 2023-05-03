//
// Created by ormequ on 27.04.23.
//

#pragma once
#include <vector>
#include "../utils/Vector.h"

struct Dimension {
    double min;
    double max;
    double step;
};

class LinearSpace {
public:
    LinearSpace();

    void addBoundary(Dimension dimension);

    Vector next();

    void clear();

    size_t size();

    Vector at(int i);
protected:
    std::vector<Dimension> space;
    Vector position;
    int dims;
    bool maxReached;
};

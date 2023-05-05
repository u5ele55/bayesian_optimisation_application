//
// Created by ormequ on 27.04.23.
//

#pragma once

#include <vector>
#include "Vector.h"

struct Dimension {
    double min;
    double max;
    double step;
};

class LinearSpace {
public:
    LinearSpace();

    void addBoundary(Dimension dimension);

    /**
     * Iterates throw linear space
     * @return current step
     * */
    Vector next();

    /**
     * Clears the iterator
     * */
    void clear();

    size_t size();

    Vector at(size_t i);

    size_t dimensions();

protected:
    std::vector<Dimension> space;
    Vector position;
    int dims;
    bool maxReached;
};

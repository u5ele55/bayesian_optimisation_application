//
// Created by ormequ on 27.04.23.
//

#include "LinearSpace.h"

LinearSpace::LinearSpace()
        : position(0),
          dims(0),
          maxReached(false) {}

void LinearSpace::addBoundary(Dimension dimension) {
    space.push_back(dimension);
    position.resize((int) space.size(), 1);
    position[(int) space.size() - 1] = dimension.min;
    dims = space.size() - 1;
}

Vector LinearSpace::next() {
    if (maxReached) {
        return {};
    }
    Vector result = position;
    maxReached = true;
    for (int i = dims; i >= 0; i--) {
        if (position[i] - 3e-7 <= space[i].max - space[i].step) {
            position[i] += space[i].step;
            maxReached = false;
            break;
        }
        position[i] = space[i].min;
    }
    return result;
}

void LinearSpace::clear() {
    for (int i = 0; i <= dims; i++) {
        position[i] = space[i].min;
    }
    maxReached = false;
}

size_t LinearSpace::size() {
    size_t res = 1;

    for (int i = 0; i <= dims; i++) {
        res *= static_cast<size_t>((space[i].max - space[i].min) / space[i].step) + 1;
    }

    return res;
}

Vector LinearSpace::at(int i) {
    clear();
    // TODO
    for (int j = 0; j < i; j++) {
        next();
    }
    return next();
}

size_t LinearSpace::dimensions() {
    return dims + 1;
}

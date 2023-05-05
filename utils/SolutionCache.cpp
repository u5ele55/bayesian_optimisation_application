//
// Created by ormequ on 05.05.23.
//

#include "SolutionCache.h"

void SolutionCache::add(const Vector& initializer, double step, const std::vector<double> &solution) {
    solutions[initializer] = {step, solution};
}

std::pair<double, std::vector<double>> SolutionCache::get(const Vector &state) {
    return solutions[state];
}

SolutionCache &SolutionCache::getInstance() {
    static SolutionCache cache;
    return cache;
}

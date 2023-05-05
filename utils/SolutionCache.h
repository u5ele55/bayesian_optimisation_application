//
// Created by ormequ on 05.05.23.
//

#pragma once

#include <map>
#include "Vector.h"

class SolutionCache {
public:
    SolutionCache(const SolutionCache&) = delete;
    SolutionCache(SolutionCache&&) = delete;
    SolutionCache& operator=(SolutionCache&&) = delete;
    SolutionCache& operator=(const SolutionCache&) = delete;

    static SolutionCache& getInstance();

    void add(const Vector& initializer, const std::vector<double> &solution);

    std::vector<double> get(const Vector &state);
private:
    SolutionCache() = default;
    std::map<Vector, std::vector<double>> solutions;
};

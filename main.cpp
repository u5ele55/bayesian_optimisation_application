#include <iostream>

#include "utils/Vector.h"
#include "forward_problem/system.h"

#include "forward_problem/RK4Solver.h"
#include "forward_problem/system.h"

int main() {
    Vector v = {1,2,3,4,5};
    Vector u = {3,2,1,1,2};

    System system(1, 0.5, 0, 1);

    RK4ForwardSolver solver(system);

    std::cout << solver.getState(10);

    return 0;
}
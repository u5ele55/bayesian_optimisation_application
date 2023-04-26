#include <iostream>

#include "utils/Vector.h"
#include "forward_problem/system.h"


int main() {
    Vector v = {1,2,3,4,5};
    Vector u = {3,2,1,1,2};

    std::cout << v.transpose() * u << '\n';

    System s(1,1,1,1);
    s.f(v);
    std::cout << v;

    return 0;
}
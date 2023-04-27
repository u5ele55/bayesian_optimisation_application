cmake_minimum_required(VERSION 3.24)
project(bayesian_optimisation_application)

set(CMAKE_CXX_STANDARD 20)

include_directories(backward_solution)
include_directories(forward_problem)
include_directories(utils)

add_executable(bayesian_optimisation_application
        backward_solution/GaussianProcesses.cpp
        backward_solution/GaussianProcesses.h
        backward_solution/IKernel.h
        backward_solution/LinearSpace.cpp
        backward_solution/LinearSpace.h
        backward_solution/SquaredExponentialKernel.cpp
        backward_solution/SquaredExponentialKernel.h
        forward_problem/AbstractForwardSolver.cpp
        forward_problem/AbstractForwardSolver.h
        forward_problem/RK4Solver.cpp
        forward_problem/RK4Solver.h
        forward_problem/System.cpp
        forward_problem/System.h
        utils/CholeskyMaster.cpp
        utils/CholeskyMaster.h
        utils/Matrix.cpp
        utils/Matrix.h
        utils/Vector.cpp
        utils/Vector.h
        main.cpp)

cmake_minimum_required(VERSION 3.24)
project(bayesian_optimisation_application)

set(CMAKE_CXX_STANDARD 20)

include_directories(backward_solution)
include_directories(forward_problem)
include_directories(utils)

add_executable(bayesian_optimisation_application
        backward_solution/GaussianProcesses.cpp
        backward_solution/GaussianProcesses.h
        backward_solution/kernel/IKernel.h
        utils/LinearSpace.cpp
        utils/LinearSpace.h
        backward_solution/kernel/SquaredExponentialKernel.cpp
        backward_solution/kernel/SquaredExponentialKernel.h
        forward_problem/AbstractForwardSolver.cpp
        forward_problem/AbstractForwardSolver.h
        forward_problem/RK4Solver.cpp
        forward_problem/RK4Solver.h
        forward_problem/RK4SolverWithNoise.cpp
        forward_problem/RK4SolverWithNoise.h
        forward_problem/System.cpp
        forward_problem/System.h
        utils/CholeskyMaster.cpp
        utils/CholeskyMaster.h
        utils/Matrix.cpp
        utils/Matrix.h
        utils/Vector.cpp
        utils/Vector.h
        main.cpp backward_solution/BayesianOptimizer.h backward_solution/BayesianOptimizer.cpp backward_solution/PendulumMSE.cpp backward_solution/PendulumMSE.h utils/SolutionCache.cpp utils/SolutionCache.h)

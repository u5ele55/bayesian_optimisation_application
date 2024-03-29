cmake_minimum_required(VERSION 3.10)
project(bayesian_optimisation_application)

set(CMAKE_CXX_STANDARD 17)

include_directories(backward_solution)
include_directories(forward_problem)
include_directories(utils)

add_executable(bayesian_optimisation_application
        backward_solution/GaussianProcesses.cpp
        backward_solution/GaussianProcesses.h
        backward_solution/functions/IFunction.h
        backward_solution/functions/SimpleFunction.h
        backward_solution/functions/SimpleFunction.cpp
        backward_solution/functions/Simple2DFunction.h
        backward_solution/functions/Simple2DFunction.cpp
        backward_solution/kernel/IKernel.h
        backward_solution/acquisition/IAcquisition.h
        backward_solution/acquisition/AcquisitionUCB.h
        backward_solution/acquisition/AcquisitionUCB.cpp
        backward_solution/acquisition/AcquisitionEI.h
        backward_solution/acquisition/AcquisitionEI.cpp
        utils/Boundaries.h
        backward_solution/kernel/SquaredExponentialKernel.cpp
        backward_solution/kernel/SquaredExponentialKernel.h
        forward_problem/FullSystemFabric.cpp
        forward_problem/FullSystemFabric.h
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
        utils/logs/AbstractLogger.h
        utils/logs/AbstractLogger.cpp
        utils/logs/FileLogger.h
        utils/logs/FileLogger.cpp
        main.cpp backward_solution/BayesianOptimizer.h backward_solution/BayesianOptimizer.cpp backward_solution/functions/PendulumMSE.cpp backward_solution/functions/PendulumMSE.h utils/SolutionCache.cpp utils/SolutionCache.h backward_solution/kernel/Matern52Kernel.cpp backward_solution/kernel/Matern52Kernel.h forward_problem/SystemFixedDissipationFabric.cpp forward_problem/SystemFixedDissipationFabric.h forward_problem/ISystemFabric.h forward_problem/SystemOnlyAngleFabric.cpp forward_problem/SystemOnlyAngleFabric.h forward_problem/SystemAngleAndSpeedFabric.cpp forward_problem/SystemAngleAndSpeedFabric.h)

target_include_directories(bayesian_optimisation_application
        PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/Eigen
        ${CMAKE_SOURCE_DIR}/libs/LBFGS)

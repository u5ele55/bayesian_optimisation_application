# bayesian_optimisation_application
Bayesian optimization used to solve the inverse problem of a dissipative pendulum

## About
This repository contains implementation of the Bayesian Optimisation and Gaussian Processes which are used to optimize parameters of dynamic system of dissipative pendulum. <br>
Program could be built with CMake (min. 3.10 version required) <br>

## Some results
All plots were made with Python using matplotlib. <br>
Black dots here are measurements with applied normal-distributed noise. Curves with opacity are results of iterations of Bayesian Optimisation. 
Blue and orange curves are measurements from original and optimized systems. <br>

1. omega = 1.5, dissipation coefficient = 1, initial angle = 1.57 ~ PI/2, initial angular speed = 1.5. Number of iteratoins: 500<br>
![Figure_1](https://github.com/u5ele55/bayesian_optimisation_application/assets/57725831/05f74e1f-e4d6-43f5-aebb-7b4437886602) <br>

1. omega = 1.25, dissipation coefficient = 0.75, initial angle = 1.57 ~ PI/2, initial angular speed = 0. Number of iteratoins: 500<br>
![Figure_2](https://github.com/u5ele55/bayesian_optimisation_application/assets/57725831/dafeedca-e7df-450e-b3b4-21f940337fce)


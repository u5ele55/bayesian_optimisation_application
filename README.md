# bayesian_optimisation_application
Bayesian optimization used to solve the inverse problem of a dissipative pendulum

## About
This repository contains implementation of the Bayesian Optimisation and Gaussian Processes which are used to optimize parameters of dynamic system of dissipative pendulum. <br>
Program could be built with CMake (min. 3.10 version required) <br>

## Some results
All plots were made with Python using matplotlib. <br>
Black dots here are measurements with applied normal-distributed noise. Curves with opacity are results of iterations of Bayesian Optimisation. 
Blue and orange curves are measurements from original and optimized systems. <br>

1. Parameters omega, dissipation coefficient, initial angle and angular speed are 0.9, 0.4, PI/2, 0.4 respectively.<br>
![изображение](https://user-images.githubusercontent.com/57725831/236898389-33a93bce-390e-4137-9012-79a2d58d4ad1.png) <br>

2. Parameters are 0.9 sqrt(2)/2, PI/2, PI/4
![изображение](https://user-images.githubusercontent.com/57725831/236898936-a805846d-e7ac-47d9-9ccf-c692116a637d.png)


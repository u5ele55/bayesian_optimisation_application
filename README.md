# bayesian_optimisation_application
Bayesian optimization used to solve the inverse problem of a dissipative pendulum

## About
This repository contains implementation of the Bayesian Optimisation and Gaussian Processes which are used to optimize parameters of dynamic system of dissipative pendulum. <br>
Program could be built with CMake (min. 3.24 version required) <br>

## Some results
All plots were made with Python using matplotlib. <br>
Black dots here are measurements with applied normal-distributed noise. Curves with opacity are results of iterations of Bayesian Optimisation. 
Blue and orange curves are measurements from original and optimized systems. <br>

1. All parameters occur in discrete space in which search is performed
Parameters omega, dissipation coefficient, initial angle and angular speed are 0.9, 0.4, PI/2, 0.4 respectively.<br>
![image](https://user-images.githubusercontent.com/99137907/236603685-f47ca335-f57e-4690-b938-d79979687115.png) <br>
There illustrated result of 30 iterations of BO. Curve that matches original was found in 12 iterations.

2. One original parameter doesn't lie in given space
Parameters are similar to (1) but with angular speed = 1.2, and dimension where speed is being searched bounded by 1. <br>
![image](https://user-images.githubusercontent.com/99137907/236605473-2b507794-0853-45d9-bb52-0721c73de3b4.png)

3. Two parameters don't fit into space
Here parameters similar to (2) but with initial angle = 1. Space consists of angles from PI/4 to PI/2 with step of PI/16. <br>
![image](https://user-images.githubusercontent.com/99137907/236605845-581083ae-5d13-4339-9c71-1e6a052f83b3.png)

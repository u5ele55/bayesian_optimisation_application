# bayesian_optimisation_application
Bayesian optimization used to solve the inverse problem of a dissipative pendulum

## About
This repository contains implementation of the Bayesian Optimisation and Gaussian Processes which are used to optimize parameters of dynamic system of dissipative pendulum. <br>
Program could be built with CMake (min. 3.10 version required) <br>

## Main information
Consider function MSE in terms of pendulum positions. Bayesian optimization works in space of parameters of pendulum and tries to optimize MSE function, which takes pendulum parameters as argument and builds it trajectory that is compared to source trajectory. <br>
**It was discovered, that MSE is very sensitive to dissipation coeffitient and thus optimization becomes complicated. We will take it as a constant and will look only for three remaining parameters: omega, initial angle and angular speed**

## Some results
All plots were made with Python using matplotlib. <br>
Black dots here are measurements with applied normal-distributed noise. Curves with opacity are results of iterations of Bayesian Optimisation. 
Blue and orange curves are measurements from original and optimized systems. <br>
<hr>

1. omega = 0.8, dissipation coefficient = 0.9, initial angle = 1.25, initial angular speed = -1.5. <br>
Number of iterations: 200. <br>
Used acquisition function: UCB<br>
![image](https://github.com/u5ele55/bayesian_optimisation_application/assets/99137907/cf3f3079-fd4b-4099-8d27-1b639df044cd)
<br>

2. omega = 1, dissipation coefficient = 0.9, initial angle = 0.987, initial angular speed = -1.3. <br>
Number of iterations: 300. <br>
Used acquisition function: EI<br>
![image](https://github.com/u5ele55/bayesian_optimisation_application/assets/99137907/766df859-9425-48ba-88d0-516f7a725904)
<br>

3. omega = 1, dissipation coefficient = 0.9, initial angle = 1.57, initial angular speed = -1.5. <br>
Number of iterations: 100. <br>
Used acquisition function: UCB<br>
![image](https://github.com/u5ele55/bayesian_optimisation_application/assets/99137907/4dd4113d-37b7-48b2-8d97-647de0e6c48b)
<br>

4. omega = 1.23, dissipation coefficient = 0.9, initial angle = 0.987, initial angular speed = -1. <br>
Number of iterations: 200. <br>
Used acquisition function: UCB<br>
![image](https://github.com/u5ele55/bayesian_optimisation_application/assets/99137907/043aadb4-472f-4b9c-ac0c-4234b900c785)
<br>

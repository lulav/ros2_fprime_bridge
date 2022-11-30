# Example 1: Spring - Mass - Dumper 

# General Info

This is a simple demonstration of a mass-spring-damper system.

![](https://user-images.githubusercontent.com/58637596/204790078-3ea8521c-d218-4a8e-961f-828165b24814.png)

# System dynamics

The system's equations of motion:

$$m\ddot x =  kf(t) -c\dot x -kx$$

and after laplace transformation (with zero I.C) we get a second order system:

$${X \over F} = {\omega_n^2 \over s^2 +2\omega_n\zeta s + \omega_n^2} $$

where the natural frequency $\omega_n = \sqrt{k \over m}$

You can choose the system's parameters `m`, `k` and `c` and choose the initial condition `x0` and `v0`.


# The controller

You can write your own controller to try stabilize the system for a given setpoint.

the default controller is a simple PID controller with the following form:

$$f(t) = {k_pe(t) + k_i\int{e(t)dt}} + k_d {d\over dt}(e(t))$$

you can tune the controller gains, $k_p$, $k_i$, $k_d$.


# Installation

clone the repository to your local machine:
                
                git clone https://github.com/lulav/ros2_fprime_bridge.git

open the repository in the VScode:

                cd ~/ros2_fprime_bridge
                code .

open the repository in the container from VScode with `reopen in container` option.

Then compile with:

                cd examples/spring_mass_dumper/
                mkdir build  
                cd build   
                cmake ..
                make   

# Run:

                ./spring_mass_dumper


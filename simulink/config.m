% This is the configuration script for the simulation
clear
close
clc

% Load the bus object
load('config.mat');

% Assign initial values for the patameters
params.m = Simulink.Parameter(1.0);
params.k = Simulink.Parameter(2.5);
params.c = Simulink.Parameter(0.3);
params.r0 = Simulink.Parameter(-1.0);
params.v0 = Simulink.Parameter(0.0);

params.kp = Simulink.Parameter(8.0);
params.ki = Simulink.Parameter(1.0);
params.kd = Simulink.Parameter(4.0);
params.r_req = Simulink.Parameter(0.0);

% Open the simulator
open('simulation.slx')
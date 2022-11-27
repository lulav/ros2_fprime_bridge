% This is the configuration script for the simulation
clear
close
clc

% Load the bus object
load('config.mat');

% Assign initial values for the patameters
params.m = 1.0;
params.k = 2.5;
params.c = 0.3;
params.r0 = -1.0;
params.v0 = 0.0;

params.kp = 0.6;
params.ki = 0.2;
params.kd = 2.0;
params.r_req = 0.0;

% Create Estimation Data Bus for Simulink Model
params_bus_info = Simulink.Bus.createObject(params);
Params = evalin('base', params_bus_info.busName);

% Cleanup
clear params_bus_info slBus1

% Open the simulator
open('simulation.slx')
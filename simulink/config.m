% This is the configuration script for the simulation
clear
close
clc
% Load the bus object
load('config.mat');

% Define the bus objects
params.m = 1;
params.k = 2.5;
params.c = 0.3;
params.r0 = -1;
params.v0 = 0;
params.kp = 8;
params.ki = 1;
params.kd = 4;
params.r_req = 0;

% Generate bus
TEMP_BUS = Simulink.Bus.createObject(params);
P_BUS_TYPE= evalin('base', TEMP_BUS.busName);
clear(TEMP_BUS.busName)
clear('TEMP_BUS')

% Make external
p_bus = Simulink.Parameter;
p_bus.Value = params;
p_bus.DataType = 'Bus: P_BUS_TYPE'; 
p_bus.CoderInfo.StorageClass = 'ImportedExtern';

% Open simulator
open('simulation.slx')
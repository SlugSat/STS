%%
% STS Shock Test Stand
% SRS Decomposition Script
%
% Caleb Cotter & Nick Jannuzzi
%
% 5/4/20
%
%% Program Inputs
close all;
clear all;
clc;

% Constants
g = 9.80665;

% SRS Response Frequencies
f_n = [30, 100, 700, 1000, 1500, 5000, 10000]; %Hz
acc_g_n = [5, 100, 1500, 2400, 4000, 4000, 2000]; %G's
Q = 10;

% Generate Systems TFs
s = tf('s');
k = 1;
zeta = 1/(2*Q);
w_n = f_n*2*pi; %rad/s

for i = 1:length(w_n)
    sys = (k*w_n(i)^2)/(s^2+2*zeta*w_n(i)*s+w_n(i)^2);
    stepinfo(sys)
    
end
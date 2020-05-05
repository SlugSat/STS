%%
% STS Shock Test Stand
% SRS Generation Script
%
% Caleb Cotter
%
% 4/30/20
%
%% Program Inputs
close all;
clear all;
clc;

t_sim = 10; %seconds
t_step = 0.001; %seconds

% SRS Response Frequencies
f_n = [30, 100, 700, 1000, 1500, 5000, 10000]; %Hz
acc_g_n = [5, 100, 1500, 2400, 4000, 4000, 2000]; %G's
Q = 10;

% Half-Sine Pulse Input Properties
t_pulse = 11E-3; %seconds

% Constants
g = 9.80665; 

%% Processing
acc_n = acc_g_n*g; %m/s

k = 1;
zeta = 1/(2*Q);
w_n = f_n*2*pi; %rad/s

[u,t] = gensig('sin', 2*t_pulse, t_sim, t_step); %Half-Sine
plot(t,u);

s = tf('s');

%%
for i = 1:length(f_n);
    H = (k*w_n(i)^2)/(s^2+2*zeta*w_n(i)*s+w_n(i)^2);
    hold on;
    step(H);
    stepinfo(H)
end


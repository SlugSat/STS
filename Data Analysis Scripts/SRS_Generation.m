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

t_sim = 250E-3; %seconds
t_step = 0.00000005; %seconds

% Constants
g = 9.80665;

% SRS Response Frequencies
f_n = [30, 100, 700, 1000, 1500, 5000, 10000]; %Hz
acc_g_n = [5, 100, 1500, 2400, 4000, 4000, 2000]; %G's
Q = 10;

% Half-Sine Shock Pulse
t_pulse = 11E-3; %seconds
a_peak_pulse = 50; %G's

[u_pulse,t_pulse] = gensig('sin', 2*t_pulse, t_pulse, t_step); %Half-Sine
u_pulse = u_pulse*a_peak_pulse*g; %Scale to m/s^2
t_zeros = ((length(t_pulse)*t_step):t_step:t_sim)';
u_zeros = zeros(length(t_zeros),1);
t = vertcat(t_pulse,t_zeros);
u = vertcat(u_pulse,u_zeros);

%% Processing
acc_n = acc_g_n*g; %m/s

k = 1;
zeta = 1/(2*Q);
w_n = f_n*2*pi; %rad/s

s = tf('s');
for i = 1:length(w_n)
    hold on;
    sys = (k*w_n(i)^2)/(s^2+2*zeta*w_n(i)*s+w_n(i)^2);
    lsim(sys,u,t);
end
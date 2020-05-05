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

t_sim = 20E-3; %seconds
t_step = 0.00000005; %seconds

% Constants
g = 9.80665;

% SRS Test Frequencies
f_n = [30, 100, 700, 1000, 1500, 5000, 10000]; %Hz
Q = 10;

% SRS Goals
acc_g_n = [5, 100, 1500, 2400, 4000, 4000, 2000]; %G's

% Half-Sine Shock Pulse
t_pulse_duration = 0.3E-3; %seconds
a_peak_pulse = 3000; %G's

[u_pulse,t_pulse] = gensig('sin', 2*t_pulse_duration, t_pulse_duration*2, t_step); %Half-Sine
u_pulse = u_pulse*a_peak_pulse*g; %Scale to m/s^2
t_zeros = ((length(t_pulse)*t_step):t_step:t_sim)';
u_zeros = zeros(length(t_zeros),1);
t = vertcat(t_pulse,t_zeros);
u = vertcat(u_pulse,u_zeros);

plot(t_pulse,u_pulse);

%% Processing
k = 1;
zeta = 1/(2*Q);
w_n = f_n*2*pi; %rad/s

% Simulate System Responses
s = tf('s');
sys_resp = zeros(length(w_n),length(t));
for i = 1:length(w_n)
    sys = (k*w_n(i)^2)/(s^2+2*zeta*w_n(i)*s+w_n(i)^2);
    sys_resp(i,:) = lsim(sys,u,t);
    %hold on;
    %lsim(sys,u,t);
end

% Extract Max Magnitude of Each Frequency
acc_max_w_n = zeros(1,length(w_n));
for i = 1:length(w_n)
    acc_max_w_n(i) = max(sys_resp(i,:));
end

hold on;
plot(f_n,acc_max_w_n./g,'x-');
plot(f_n,acc_g_n,'o-');
set(gca, 'XScale', 'log', 'YScale', 'log');
xlabel("Frequency (Hz)");
ylabel("Acceleration (g)");
legend("Two Boobs in MATLAB","NASA GEVS");

delta_x = 0.5*a_peak_pulse*t_pulse_duration^2
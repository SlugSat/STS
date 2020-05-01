%%
% STS Shock Test Stand
% Accelerometer Data FFT Script
%
% Caleb Cotter
%
% 4/30/20
%
%%
close all;
clear all;
clc;

acc_data = [0.0 0.05 0.12 0.3 0.6 0.75 0.9 0.95 1 0.95 0.9 0.75 0.6 0.3 0.12 0.05 0];
t = linspace(0,1,length(acc_data)); %time series of data
Fs = 1/t(2); %sampling rate in Hz

acc_fft = fft(acc_data);
P2 = abs(acc_fft/length(acc_data));
P1 = P2(1:length(acc_data)/2+1);
P1(2:end-1) = 2*P1(2:end-1);

figure(1);
plot(t,acc_data);
title('Acceleration vs. Time')
xlabel('t (seconds)')
ylabel('Acceleration (g)')

figure(2);
f = Fs*(0:(length(acc_data)/2))/length(acc_data);
plot(f,P1)
title('Single-Sided Amplitude Spectrum of Accleration')
xlabel('f (Hz)')
ylabel('|Acc(f)|')


%% HammerImpactCalcs.m
%   For usage with development of the SlugSat Shock Test Stand (STS)%
%   Created by : Nick Jannuzzi & Caleb Cotter%
%   Property of UCSC SlugSat Program
%   Each section can be run individually to calculate different portions
%   for the system.
close all;
clear all;
clc;

%% Deflection Plate Dynamics Transfer Function
% Plate dimensions and material paramaters (in meters)
Plate_Length = 0.2; 
Plate_Width = 0.1;
Plate_Thickness = 0.00635*2;

% Look up this value for the material (no there is not an Old's Modulus)
Youngs_Modulus = 69e9;          % Pascals
Desired_Deflection = 0.135e-3;  % Meters

% Calculate the equivalent spring constant K of the beam, in Newtons / Meter
Cantilever_K = (Plate_Width*Plate_Thickness^3*Youngs_Modulus)/(4*Plate_Length^2);

% Calculate mass of plate from M = DV
% Material Density
Material_Density = 2700;                                    % Kilograms / Meters^3
Plate_Volume = Plate_Length*Plate_Width*Plate_Thickness;    % Meters^3
Plate_Mass = Material_Density*Plate_Volume;

% Natural Frequency of Plate + Satellite
Sat_Mass = 2;                   % Kilograms
T_Mass = Plate_Mass + Sat_Mass; % Kilograms
Wo = sqrt(Cantilever_K/T_Mass); % Radians/Second

% Damping ratio of Material (Look this up)->Damping Coefficient
Damp_Ratio = 0.5e-4; %(Aluminum)

% Damping coefficient (zeta) = viscous coefficient(lambda)/2sqrt(km) since
% our beam is of non-negligible thickness, lambda is the damping ratio of
% the material rather than of air.
Damp_Coefficient = Damp_Ratio/(2*sqrt(Cantilever_K*T_Mass));

% Q-Factor (Don't really need this, but put it here anyways
Q_Factor = 1/(2*Damp_Coefficient);

% 2nd Order System Model (Force -> Deflection Transfer Function)
s = tf('s');
G = 1/((1/Wo^2)*s^2+(2*Damp_Coefficient/Wo)*s+1)
% Need to set step amplitude to non unit value
opt = stepDataOptions('StepAmplitude', Desired_Deflection);
step(G,opt)
Period = 1/(2*pi*Wo)

% Energy stored in the plate (Joules)
U_Plate = 0.5*Cantilever_K*Desired_Deflection^2;

%% Calculation of Hammer Arm Kinetic Energy Given Masses and Length of Arm
% Constants
g = 9.80665; % m/s

% Hammer Arm Parameters
M_Arm = 1;
M_Head = 1;
L_Arm = 1;

% Center of mass location for Compound Pendulum
Xcm = (M_Arm*L_Arm/2 + M_Head*L_Arm)/(M_Head+M_Arm)

% Hammer arm inertia can be calculate by representing it as a uniform rod
% of length L with a point mass attached at L
Hammer_MoI = 1/3*M_Arm*L_Arm^2 + M_Hammer*L_Arm^2;

% Compound pendulum period equation
Compound_Pendulum_Period = 2*pi*sqrt(Hammer_MoI/(M_Hammer*M_Arm*g*Xcm));

% Frequency of compound pendulum
Compound_Pendulum_Frequency = 1/Compound_Pendulum_Period;

% Angular Velocity
AngV = 2*pi*Compound_Pendulum_Frequency;

% Kinetic Energy of Pendulum
KE_Pendulum = 0.5*Hammer_MoI*AngV^2;

%% Calculate Deflection in Cantilever Beam given Force 
% Parameters
Elasticity_Modulus = 1; %(Young's Modulus)
Beam_Height = 1;
Beam_Thickness = 1;

P = 1; %(Point Load)
% Distance from support to P
a = 1;
% Distance from P to end of cantilever beam
b = 1;%(we never actually use this, don't worry)

% Area Moment of Inertia for Cantilever Beam
AI = 1;

% Defelction of a beam, with a concentrated load P at distance a from the
% support can be found from the equation: 
%
% Beam_Deflection = (P*a^2)/(6*AI*Elasticity_Modulus)*(2*a);
%
% This can be rearranged to find the load needed to obtain a desired
% deflection.

% Deflection we need for acceleration profile
Desired_Deflection = 0.135e-3;

% Calculate impulse force needed to obtain deflection in Aluminum plate
Load_Needed = (6*AI*Elasticity_Modulus*Desired_Deflection)/(2*a^3);

%% Calculating Strain Energy Stored in a Beam


%%% HammerImpactCalcs.m
%For usage with development of the SlugSat Shock Test Stand (STS)%
%Created by : Nick Jannuzzi & Caleb Cotter%
%Property of UCSC SlugSat program%
%Each section can be run individually to calculate different portions fo
%the system
clear all


%% Deflection Plate sizing and calculation of transfer function characteristics
%Plate dimensions and material paramaters
Plate_Length = 0.2; 
Plate_Width = 0.1;
Plate_Thickness = 0.00635*3;
%Look up this value for the material
Youngs_Modulus = 69e9;

%calculate the equivalent spring constant K of the beam, in Newtons/meter^2
% 1 N/m^2 can also be written as 1 Pascal(Pa)
Cantilever_K = (Plate_Width*Plate_Thickness^3*Youngs_Modulus)/(4*Plate_Length^2);


 

%Calculate mass of plate from M = DV
%Material Density
Material_Density = 2700; %(kg/m^3)
Plate_Volume = Plate_Length*Plate_Width*Plate_Thickness;
Plate_Mass = Material_Density*Plate_Volume;

%Natural Frequency of Plate+Satellite
Sat_Mass = 2 ;
T_Mass = Plate_Mass + Sat_Mass;
Wo = sqrt(Cantilever_K/T_Mass);

%Damping ratio of Material (Look this up)->Damping Coefficient
Damp_Ratio = 0.5e-4; %(Aluminum)
%Damping coefficient (zeta) = viscous coefficient(lambda)/2sqrt(km)
%since our beam is of non-negligible thickness, lambda is the damping ratio
%of the material rather than of air
Damp_Coefficient = Damp_Ratio/(2*sqrt(Cantilever_K*T_Mass));

%Q-Factor (Don't really need this, but put it here anyways
Q_Factor = 1/(2*Damp_Coefficient);


%the corresponding 2nd order system model for the deflection
%plate/cantilver beam
s = tf('s');
G = 1/((1/Wo^2)*s^2+(2*Damp_Coefficient/Wo)*s+1)
%need to set step amplitude to non unit value
opt = stepDataOptions('StepAmplitude',0.000135);
step(G,opt)
Period = 1/(2*pi*Wo)
%% Calculation of Hammer Arm Kinetic Energy Given Masses and Length of Arm

%constants
Gravity = 9.80665


%Hammer Arm Parameters
M_Arm = 1;
M_Head = 1;


L_Arm = 1;

%Center of mass location for Compound Pendulum
Xcm = (M_Arm*L_Arm/2 + M_Head*L_Arm)/(M_Head+M_Arm)


%Hammer arm inertia can be calculate by representing it as a 
%uniform rod of length L with a point mass attached at L
Hammer_MoI = 1/3*M_Arm*L_Arm^2 + M_Hammer*L_Arm^2;
%compound pendulum period equation

Compound_Pendulum_Period = 2*pi*sqrt(Hammer_MoI/(M_Hammer*M_Arm*Gravity*Xcm));

%Frequency of compound pendulum
Compound_Pendulum_Frequency = 1/Compound_Pendulum_Period;

%Angular Velocity
AngV = 2*pi*Compound_Pendulum_Frequency;

%Kinetic Energy of a pendulum
KE_Pendulum = 0.5*Hammer_MoI*AngV^2;




%% Calculate Deflection in Cantilever Beam given 
%Parameters
Elasticity_Modulus = 1; %(Young's Modulus)
Beam_Height = 1;
Beam_Thickness = 1;

P = 1; %(Point Load)
%distance from support to P
a = 1;
%distance from P to end of cantilever beam
b = 1;%(we never actually use this, don't worry)



%Area Moment of Inertia for Cantilever Beam
AI = 1;

%Defelction of a beam, with a concentrated load P at distance a
%from the support can be found from the equation:   
%Beam_Deflection = (P*a^2)/(6*AI*Elasticity_Modulus)*(2*a); 
%this can be rearranged to find the load needed to obtain a desired
%deflection

%deflection we need for acceleration profile
Desired_Deflection = 0.135e-3;

%calculate impulse force needed to obtain desired deflection in aluminum
%plate
Load_Needed = (6*AI*Elasticity_Modulus*Desired_Deflection)/(2*a^3);

%% Calculating Strain Energy Store in a beam


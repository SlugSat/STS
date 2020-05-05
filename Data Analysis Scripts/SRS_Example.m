close all;
clear all;
clc;

ymax=[];
ff=[];
fmin=1;
fmax=1000;
n=100;
qv=(fmax/fmin)^(1/n);
T=1/input('freq');
Q=10;

for i=0:1:n-1
    fn=fmin*qv^i;
    ff=[ff,fn];
    
    wn=2*pi*fn;
    A=wn*T/2/Q;
    B=wn*T*sqrt(1-1/4/Q/Q);
    
    b0=1-exp(-A)*sin(B)/B;
    b1=2*exp(-A)*(sin(B)/B-cos(B));
    b2=exp((-2)*A)-exp(-A)*sin(B)/B;
    a1=(-2)*exp((-1)*A)*cos(B);
    a2=exp((-2)*A);
    
    BB=[b0,b1,b2];
    AA=[-a1,-a2];
    
    y=filter(1/T,BB,AA);
    yy=max(y);
    ymax=[ymax,yy];
end
plot(ff,ymax)
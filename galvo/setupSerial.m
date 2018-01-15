% This script sets up the serial on the nidaq to control the galvos. 
% It is good to check the hardware connections so that the defined analog 
% outputs match the needs of the system.

addpath(genpath(pwd));
%%
s = daq.createSession('ni');

% choose ao0-ao3 as the analog outputs of the devices

% galvos for the sensor
s.addAnalogOutputChannel('Dev1','ao0','Voltage');
s.addAnalogOutputChannel('Dev1','ao1','Voltage');

% galvos for the laser
s.addAnalogOutputChannel('Dev1','ao2','Voltage');
s.addAnalogOutputChannel('Dev1','ao3','Voltage');
s.Rate = 10000;

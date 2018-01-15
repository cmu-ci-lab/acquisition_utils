cd('C:\Users\Sotiris\Dropbox (Personal)\UoT_Internship\Projects\SPAD_Servo_Control')
addpath(genpath(pwd));

%% I. Set a new nidaq session and add the analog outputs. 

s = daq.createSession('ni');

% choose a00-ao1 as the analog outputs of the devices
s.addAnalogOutputChannel('Dev1','ao0','Voltage');
s.addAnalogOutputChannel('Dev1','ao1','Voltage');
s.Rate = 10000;

%% II. 
% Simple Example

% define a direction vector 
% dir = [1;2; 3];
% 
% voltVect = galvo_vector2angle(dir);
% 
% setLaserPosition(s, voltVect);

for i = -10:2:-2
    for j = -3:2:7
        setLaserPosition(s, [j, i])
        pause(10);
    end
end

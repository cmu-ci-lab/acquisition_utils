function [ s ] = startSerial( rate )
% Sets up the serial of a National Instruments device of 4 channels for use
% with the Thorlabs galvos.

if (nargin < 1)
    serialRate = 10000;
else
    serialRate = rate;
end

s = daq.createSession('ni');

% choose ao0-ao3 as the analog outputs of the devices

% galvos for the sensor
s.addAnalogOutputChannel('Dev1','ao0','Voltage');
s.addAnalogOutputChannel('Dev1','ao1','Voltage');

% galvos for the laser
s.addAnalogOutputChannel('Dev1','ao2','Voltage');
s.addAnalogOutputChannel('Dev1','ao3','Voltage');
s.Rate = serialRate;


end


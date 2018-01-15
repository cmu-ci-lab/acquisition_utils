function prev = setLaserPosition(s,curr,prev)
% Smoothly move galvo to new position.
%
% s - current nidaq session
% curr - 2-element vector of voltages for 2-axis galvo target position
% prev - 2-element vector of voltages for 2-axis galvo orig position
%
% To create a nidaq session, execute the following code:
%   s = daq.createSession('ni');
%   s.addAnalogOutputChannel('Dev1','ao0','Voltage');
%   s.addAnalogOutputChannel('Dev1','ao1','Voltage');
%   s.Rate = 10000;

assert(length(curr) == 2);

limit = 10;  % Limit to +-10 volts
curr = max(curr,-limit);
curr = min(curr,limit);

if ((nargin < 3) || isempty(prev)),
	prev = [0 0];
end

N = 1000;
weight = linspace(0,1,N)';
weight = 3.*weight.^2- 2.*weight.^3;
pos = [prev(1)*(1-weight)+curr(1)*weight prev(2)*(1-weight)+curr(2)*weight];
pos = min(pos,limit);
pos = max(pos,-limit);
s.queueOutputData(pos);

prev = curr;

s.startForeground;

function [  ] = showLaserWall( s, limit, delay, step )
% Positions the galvos from -limit:limit (voltage) so that the laser
% defines the minimum and maximum positions on the wall.

% s -  serial port 
% limit - voltage limit in Volts, 10 for the GVS012/
% delay - delay in seconds between the different positions (0.3 sec is
%         good)
% step - voltage step in Volts, 0.2 is good


[voltx, volty] = meshgrid(-limit:step:limit, -limit:step:limit);

for i = 1:size(voltx, 1) 
    for j = 1:size(voltx, 2)
        
        voltVec = [voltx(i, j) volty(i, j)];
        setLaserPosition(s, voltVec);
        pause(delay);
        
        
    end
end

end

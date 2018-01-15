function [  ] = showWallLimits( s, limit, delay )
% Positions the galvos from -limit:limit (voltage) so that the laser
% defines the minimum and maximum positions on the wall.

% s -  serial port 
% limit - voltage limit in Volts, 10 for the GVS012/
% delay - delay in seconds between the different positions (2 sec is
%         good)

voltx = [-limit limit];
volty = [-limit limit];


for i = 1:size(voltx, 1) 
    for j = 1:size(voltx, 2)
        
        voltVec = [voltx(i, j) volty(i, j)];
        setLaserPosition(s, voltVec);
        pause(delay);
        
        
    end
end

end

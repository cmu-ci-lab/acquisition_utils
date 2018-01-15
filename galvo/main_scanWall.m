global first;

first = 1;

clc;
% first line for laser vertical scanline, second for sensor vertical scanline 

% these values are good for parabola scanning (3D printed 11cm height, 8cm
% width)
% for a similar plane check the main_2galvos comments.
%
% verticalLine.laser = -6:0.2:-3.1;
% verticalLine.sensor = -3:0.2:-0.1;
% 
% laserx = 10;
% sensors = 9.6:-0.2:6.6;

%%%% if you want to just scan a line %%%%%%%
%
% verticalLine.laser = -4.6;
% verticalLine.sensor = -1.5;
% 
% laserx = 10;
% sensors = 2:0.4:9.2;
%%%%%%%%%%%%%%%%%%


% % % % % % % calibration of the sensor-to-wall positions using direct light
% % % % verticalLine.laser = -3:0.1:3;
% % % % laserx = 10;
% % % % verticalLine.sensor = -3:0.1:3;
% % % % sensors = 2:0.1:9.2;
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % 

step = 0.1;
acTime = 35; %sec


% verticalLine.laser = -5.6:3*step:-4.4;
% verticalLine.sensor = -2.0:3*step:-0.8;
% horizontalLine.laser = 6.35:4*step:10;
% horizontalLine.sensor = 7.15:-4*step:2;

% verticalLine.laser = -5.22:step:-4.92;

% mesh scanning
% verticalLine.laser = linspace(-5.22, -4.42, 20);
% verticalLine.sensor = linspace(-1.823, -1.023, 20);
% horizontalLine.laser = linspace(1.2, -1.3, 100);
% horizontalLine.sensor = -1;

% scanlines

verticalLine.laser = -4.92;
verticalLine.sensor = -1.523;
horizontalLine.laser = linspace(1.2, -1.3, 100);
horizontalLine.sensor = -1;



% laser left 1.3, right -1.3

fprintf('Estimated time is: %d seconds\n', length(verticalLine.laser)*length(horizontalLine.laser)*length(horizontalLine.sensor)*acTime);
%
pause(4);

fileId = 0;

for vertIdx = 1:length(verticalLine.laser)
    for horLasIdx = 1:length(horizontalLine.laser)
        for horSensIdx = 1:length(horizontalLine.sensor)
%             fileId
            % get sensor and laser positions
            laserx = horizontalLine.laser(horLasIdx);
            lasery = verticalLine.laser(vertIdx);
            sensorx = horizontalLine.sensor(horSensIdx);
            sensory = verticalLine.sensor(vertIdx);

            
            %
            filename = sprintf('parabolaAlum%.5d.out',fileId);
            
            fileId = fileId + 1;
            % give the voltage input to the galvos
            setLaserAndSensorPosition(s, [sensorx sensory laserx lasery]);
            
            % capture histogram for this position
%             scanWallCaptureHistograms
            
            first = 0;
            pause();
            
        end
    end
end
%%

disp('Scanning ended....Stopping picoharp');

stopPihocarp;

disp('Picoharp Stopped')

classdef Galvo < handle
	properties (Constant)
		MAX_VOLTAGE = 10,
	end
    
	properties (SetAccess = private)
		daqSession,
		currentPosition,
		galvoID,
	end
    
	methods
		function obj = Galvo(ID)
			if (nargin < 1),
				ID = 1;	% 1: SPAD galvo; 2: laser galvo.
			end;
			daqSession = daq.createSession('ni');

			if (ID == 1),
				daqSession.addAnalogOutputChannel('Dev1','ao0','Voltage');
				daqSession.addAnalogOutputChannel('Dev1','ao1','Voltage');
			elseif (ID == 2)
				daqSession.addAnalogOutputChannel('Dev1','ao2','Voltage');
				daqSession.addAnalogOutputChannel('Dev1','ao3','Voltage');
			else
				error('Invalid galvo ID: %d.', ID);
			end;
			obj.galvoID = ID;
			obj.daqSession.Rate = 10000;
			obj.currentPosition = [0 0];
			newPosition = [0 0];

			newPosition = max(newPosition, - Galvo.MAX_VOLTAGE);
			newPosition = min(newPosition, Galvo.MAX_VOLTAGE);
			N = 1000;
			weight = linspace(0, 1, N)';
			weight = 3 * weight .^ 2 - 2 * weight .^ 3;
			pos = [prev(1) * (1 - weight) + obj.currentPosition(1) * weight,...
				prev(2) * (1 - weight) + obj.currentPosition(2) * weight];
			pos = min(pos, Galvo.MAX_VOLTAGE);
			pos = max(pos, - Galvo.MAX_VOLTAGE);
			obj.daqSession.queueOutputData(pos);
			obj.daqSession.startForeground;
			obj.currentPosition = newPosition;
		end

		function [] = goto(obj, newPosition)
			assert(length(newPosition) == 2);
			if (any(newPosition(:) > Galvo.MAX_VOLTAGE) || any(newPosition(:) < Galvo.MAX_VOLTAGE))
				warning('Position exceeds voltage limits, truncated to limit.');
			end;
			newPosition = max(newPosition, - Galvo.MAX_VOLTAGE);
			newPosition = min(newPosition, Galvo.MAX_VOLTAGE);
			N = 1000;
			weight = linspace(0, 1, N)';
			weight = 3 * weight .^ 2 - 2 * weight .^ 3;
			pos = [prev(1) * (1 - weight) + obj.currentPosition(1) * weight,...
				prev(2) * (1 - weight) + obj.currentPosition(2) * weight];
			pos = min(pos, Galvo.MAX_VOLTAGE);
			pos = max(pos, - Galvo.MAX_VOLTAGE);
			obj.daqSession.queueOutputData(pos);
			obj.daqSession.startForeground;
			obj.currentPosition = newPosition;
		end
		
		function [] = moveinc(obj, moveInVolts, numMovements)
			assert(length(moveInVolts) == 2);
			for iterMovement = 1:numMovements,
				newPosition = obj.currentPosition + moveInVolts;
				obj.goto(newPosition);
			end;
		end

		function pos = getpos(obj)
			pos = obj.currentPosition;
		end
	end
end

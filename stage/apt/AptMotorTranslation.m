classdef AptMotorTranslation < handle
	properties (Constant)
		MOTOR_PROGID = 'MGMOTOR.MGMotorCtrl.1',
		CHAN1_ID = 0,
	end
    
	properties (SetAccess = private)
		fig,
		ctrl,
		maxAcc,
		maxVel,
	end
    
	methods
		function obj = AptMotorTranslation(hwSerial, maxAcc, maxVel)
			if (nargin < 2),
				maxAcc = 0.25;	% APT default: 1;
			end;
			if (nargin < 3),
				maxVel = 0.5;	% APT default: 2;
			end;
			obj.fig = figure();

			% Create the active x control for the MOTOR control
			obj.ctrl = actxcontrol(AptMotorTranslation.MOTOR_PROGID,...
								[20 20 600 400], obj.fig);

			% Sets the hardware serial number
			obj.ctrl.HWSerialNum = hwSerial;
			obj.ctrl.StartCtrl();    
			drawnow();
			obj.ctrl.SetVelParams(AptMotorTranslation.CHAN1_ID,...
								0, maxAcc, maxVel);
			obj.maxAcc = maxAcc;
			obj.maxVel = maxVel;
		end

		function [] = home(obj)
			obj.ctrl.MoveHome(AptMotorTranslation.CHAN1_ID, true);
		end
		
		function [] = goto(obj, locationInMm)
			obj.ctrl.MoveAbsoluteEx(AptMotorTranslation.CHAN1_ID,...
									locationInMm, 0, true);
		end
		
		function [] = moveinc(obj, distanceInMm, numMovements)
			for iterMovement = 1:numMovements,
				obj.ctrl.MoveRelativeEx(AptMotorTranslation.CHAN1_ID,...
										distanceInMm, 0, true);
			end;
		end

		function [] = translate(obj, distanceInMm)
			obj.ctrl.MoveRelativeEx(AptMotorTranslation.CHAN1_ID,...
									distanceInMm, 0, true);
		end

		function pos = getpos(obj)
			pos = obj.ctrl.GetAbsMovePos_AbsPos(AptMotorTranslation.CHAN1_ID);
		end
		
		function [] = setvelparams(obj, maxAcc, maxVel)
			obj.ctrl.SetVelParams(AptMotorTranslation.CHAN1_ID,...
									0, maxAcc, maxVel);
			obj.maxAcc = maxAcc;
			obj.maxVel = maxVel;
		end

		function [] = delete(obj)
			obj.ctrl.StopCtrl();
			obj.ctrl.delete();
			close(obj.fig);
		end
	end
end
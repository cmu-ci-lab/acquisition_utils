classdef AptMotorRotation < handle
	properties (Constant)
		MOTOR_PROGID = 'MGMOTOR.MGMotorCtrl.1',
		CHAN1_ID = 0,
		ROT_MOVE_POS = 1,
		ROT_MOVE_NEG = 2,
		ROT_MOVE_SHORT = 3,
	end
    
	properties (SetAccess = private)
		fig,
		ctrl,
		rotMove,
		maxAcc, 
		maxVel,
	end
    
	methods
		function obj = AptMotorRotation(hwSerial, rotMove, maxAcc, maxVel)
			if (nargin < 2),
				rotMove = AptMotorRotation.ROT_MOVE_SHORT;
			end;
			if (nargin < 3),
				maxAcc = 5;	% APT default: 50;
			end;
			if (nargin < 4),
				maxVel = 10;	% APT default: 25;
			end;
			obj.fig = figure();

			% Create the active x control for the MOTOR control
			obj.ctrl = actxcontrol(AptMotorRotation.MOTOR_PROGID,...
								[20 20 600 400], obj.fig);

			% Sets the hardware serial number
			obj.ctrl.HWSerialNum = hwSerial;
			obj.ctrl.StartCtrl();    
			drawnow(); 
% 			obj.ctrl.SetRotStageModes(rotMove, 2);
			obj.rotMove = rotMove;
			obj.ctrl.SetVelParams(AptMotorRotation.CHAN1_ID,...
								0, maxAcc, maxVel);
			obj.maxAcc = maxAcc;
			obj.maxVel = maxVel;
		end
		
		function [] = home(obj)
			obj.ctrl.MoveHome(AptMotorRotation.CHAN1_ID, true);
		end
        
		function [] = goto(obj, angleInDegrees)
			obj.ctrl.MoveAbsoluteRot(AptMotorRotation.CHAN1_ID,...
									angleInDegrees, 0,...
									obj.rotMove, true);
		end

		function [] = rotate(obj, angleInDegrees)
			obj.ctrl.MoveRelativeEx(AptMotorRotation.CHAN1_ID,...
									angleInDegrees, 0, true);
		end
        
		function pos = getpos(obj)
			pos = obj.ctrl.GetAbsMovePos_AbsPos(AptMotorRotation.CHAN1_ID);
		end
		
		function [] = setrotparams(obj, rotMove)
% 			obj.ctrl.SetRotStageModes(rotMove, 2);
			obj.rotMove = rotMove;
		end
		
		function [] = setvelparams(obj, maxAcc, maxVel)
			obj.ctrl.SetVelParams(AptMotorRotation.CHAN1_ID,...
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
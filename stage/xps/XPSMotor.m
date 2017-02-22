classdef XPSMotor < handle
	properties (Constant)
		Port = 5001,
		TimeOut = 60.0,
        Group = 'Group1',
        Positioner = 'Group1.Pos',
	end
    
	properties (SetAccess = private)
        ip,
		socketID,
		errorCode,
	end
    
	methods
		function obj = XPSMotor(ip)
			obj.ip = ip;
			XPS_load_drivers;
			% Connect to XPS
			obj.socketID = TCP_ConnectToServer(obj.ip, XPSMotor.Port, XPSMotor.TimeOut);
			if (obj.socketID < 0)
				disp('Connection to XPS failed, check ip & Port');
				return ;
			end
			
			[obj.errorCode] = GroupKill(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupKill!']);
				return ;
			end
			[obj.errorCode] = GroupInitialize(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp(['Error ' num2str(obj.errorCode) ' occurred while doing GroupInitialize!']);
				return ;
			end
		end

		function [] = home(obj)
			[obj.errorCode] = GroupKill(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupKill!']);
				return ;
			end
			[obj.errorCode] = GroupInitialize(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp(['Error ' num2str(obj.errorCode) ' occurred while doing GroupInitialize!']);
				return ;
			end
			[obj.errorCode] = GroupHomeSearch(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp(['Error ' num2str(obj.errorCode) ' occurred while doing GroupHomeSearch!']);
				return ;
			end
		end
		
		function [] = goto(obj, locationInMm)
			[obj.errorCode] = GroupMoveAbsolute(obj.socketID, XPSMotor.Positioner, locationInMm);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupMoveAbsolute!']);
				return ;
			end
		end
		
		function [] = moveinc(obj, distanceInMm, numMovements)
			for iterMovement = 1:numMovements,
				[obj.errorCode] = GroupMoveRelative(obj.socketID, XPSMotor.Positioner, distanceInMm);
				if (obj.errorCode ~= 0)
					disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupMoveAbsolute!']);
					return ;
				end
			end;
		end

		function [] = translate(obj, distanceInMm)
			[obj.errorCode] = GroupMoveRelative(obj.socketID, XPSMotor.Positioner, distanceInMm);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupMoveAbsolute!']);
				return ;
			end
		end

		function pos = getpos(obj)
			[obj.errorCode, pos] = GroupPositionCurrentGet(obj.socketID, XPSMotor.Positioner, 1);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupPositionCurrentGet!']);
				return ;
			end
		end
		
		function [] = setvelparams(obj, maxAcc, maxVel)
% 			obj.ctrl.SetVelParams(AptMotorTranslation.CHAN1_ID,...
% 									0, maxAcc, maxVel);
% 			obj.maxAcc = maxAcc;
% 			obj.maxVel = maxVel;
		end

		function [] = delete(obj)
			% Kill the group
			[obj.errorCode] = GroupKill(obj.socketID, XPSMotor.Group);
			if (obj.errorCode ~= 0)
				disp (['Error ' num2str(obj.errorCode) ' occurred while doing GroupKill!']);
				return ;
			end
			TCP_CloseSocket(obj.socketID);
		end
	end
end
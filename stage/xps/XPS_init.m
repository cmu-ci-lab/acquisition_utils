%%
XPS_load_drivers;

%%
% Set connection parameters
IP = '192.168.0.254';
Port = 5001;
TimeOut = 60.0;
% Connect to XPS
socketID = TCP_ConnectToServer (IP, Port, TimeOut);

%%
if (socketID < 0)
	disp 'Connection to XPS failed, check IP & Port' ;
	return ;
end

%%
group = 'Group1' ;
positioner = 'Group1.Pos' ;
% Kill the group
[errorCode] = GroupKill(socketID, group);
if (errorCode ~= 0)
	disp (['Error ' num2str(errorCode) ' occurred while doing GroupKill ! ']);
	return ;
end

%%
% Initialize the group
[errorCode] = GroupInitialize(socketID, group);
if (errorCode ~= 0)
	disp (['Error ' num2str(errorCode) ' occurred while doing GroupInitialize ! ']);
	return ;
end

%%
% Home search
[errorCode] = GroupHomeSearch(socketID, group);
if (errorCode ~= 0)
	disp (['Error ' num2str(errorCode) ' occurred while doing GroupHomeSearch ! ']);
	return ;
end

%%
% Make a move
[errorCode] = GroupMoveAbsolute(socketID, positioner, 20.0);
if (errorCode ~= 0)
	disp (['Error ' num2str(errorCode) ' occurred while doing GroupMoveAbsolute ! ']);
	return ;
end

%%
% Get current position
[errorCode, currentPosition] = GroupPositionCurrentGet(socketID, positioner, 1);
if (errorCode ~= 0)
	disp (['Error ' num2str(errorCode) ' occurred while doing GroupPositionCurrentGet! ']);
	return ;
else
	disp (['Positioner ' positioner ' is in position ' num2str(currentPosition)]);
end

%%
% Close connection
TCP_CloseSocket(socketID);
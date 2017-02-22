classdef FilterWheel < handle
	properties (Constant)
		WHEEL_PROGID = 'OptecHID_FilterWheelAPI.FilterWheels',
	end
    
	properties (SetAccess = private)
		filterWheelManager,
		filterWheelList,
		filterWheel,
	end
    
	methods
		function obj = FilterWheel()
			obj.filterWheelManager = actxserver(FilterWheel.WHEEL_PROGID);
			obj.filterWheelList = obj.filterWheelManager.invoke('FilterWheelList');
			obj.filterWheel = obj.filterWheelList.invoke('Item', 0);
		end

		function [] = home(obj)
			obj.filterWheel.invoke('HomeDevice');
		end
		
		function [] = goto(obj, filterPosition)
			obj.filterWheel.set('CurrentPosition', filterPosition);
		end

		function pos = getpos(obj)
			pos = obj.filterWheel.invoke('CurrentPosition');
		end
		
		function numFilters = getnumfilters(obj)
			numFilters = obj.filterWheel.invoke('NumberOfFilters');
		end
		
		function id = getid(obj)
			id = obj.filterWheel.invoke('WheelID');
		end
		
		function firmware = getfirmware(obj)
			firmware = obj.filterWheel.invoke('FirmwareVersion');
		end

		function [] = delete(obj)
% 			delete(obj.filterWheel);
% 			delete(obj.filterWheelList);
			delete(obj.filterWheelManager);
		end
	end
end
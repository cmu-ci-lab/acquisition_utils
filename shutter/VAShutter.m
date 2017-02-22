classdef VAShutter < handle
	properties (Constant)
		BaudRate = 9600,
        DataBits = 8,
        FlowControl = 'none',
        Parity = 'none',
        StopBits = 1,
	end
    
	properties (SetAccess = private)
		serialPort,
		handle,
        currentPos,
	end
    
	methods
		function obj = VAShutter(serialPort)
            obj.serialPort = serialPort;
            obj.handle = serial(obj.serialPort);
            set(obj.handle, 'BaudRate', VAShutter.BaudRate);
            set(obj.handle, 'DataBits', VAShutter.DataBits);
            set(obj.handle, 'FlowControl', VAShutter.FlowControl);
            set(obj.handle, 'Parity', VAShutter.Parity);
            set(obj.handle, 'StopBits', VAShutter.StopBits);
            fopen(obj.handle);
            obj.close();
            obj.currentPos = 0;
		end

		function [] = reset(obj)
            fprintf(obj.handle, 'C');
		end

		function [] = trigger(obj)
            fprintf(obj.handle, 'B');
		end

		function [] = open(obj)
            fprintf(obj.handle, '@');
            obj.currentPos = 1;
		end

		function [] = close(obj)
            fprintf(obj.handle, 'A');
            obj.currentPos = 0;
        end

		function pos = getpos(obj)
			pos = obj.currentPos;			
        end
        
        function [] = flip(obj)
            if (obj.currentPos == 1),
                obj.close();
            else
                obj.open();
            end;
        end

		function [] = delete(obj)
            obj.close();
			fclose(obj.handle);
            delete(obj.handle);
		end
	end
end
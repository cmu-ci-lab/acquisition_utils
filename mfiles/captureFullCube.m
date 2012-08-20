function cube = captureFullCube(handle, varargin)

wavelengths = 420:10:720;
cube = captureCube(handle, wavelengths, varargin{:});

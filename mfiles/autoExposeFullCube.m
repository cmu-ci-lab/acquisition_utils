function exposures = autoExposeFullCube(handle, varargin)

wavelengths = 420:10:720;
exposures = autoExposeCube(handle, wavelengths, varargin{:});
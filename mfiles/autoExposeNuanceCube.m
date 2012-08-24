function exposures = autoExposeNuanceCube(handle, varargin)

wavelengths = 420:10:720;
exposures = autoExposeCube(handle, wavelengths, varargin{:});

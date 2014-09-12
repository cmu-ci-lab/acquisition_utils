function exposures = autoExposeNuanceCube(handle, varargin)

wavelengths = getNuanceWavelengths;
exposures = autoExposeCube(handle, wavelengths, varargin{:});

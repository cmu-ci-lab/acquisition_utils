function cube = captureNuanceCube(handle, varargin)

wavelengths = getNuanceWavelengths;
cube = captureCube(handle, wavelengths, varargin{:});

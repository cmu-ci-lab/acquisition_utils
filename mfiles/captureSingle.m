function im = captureSingle(handle, wavelength, exposure)

if ((nargin < 3) || isempty(exposure)),
	exposure = autoExposeSingle(handle, wavelength);
end;

if (numel(wavelength) ~= 1),
	warning('More than one wavelengths provided. Only first wavelength will be used.')
	wavelength = wavelength(1);
end;

if (numel(exposure) ~= 1),
	warning('More than one exposures provided. Only first exposure will be used.')
	exposure = exposure(1);
end;

im = nuancecapture(handle.camera, handle.filter, wavelength, exposure);

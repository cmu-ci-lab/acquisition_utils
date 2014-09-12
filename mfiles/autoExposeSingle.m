function exposure = autoExposeSingle(handle, wavelength)

if (numel(wavelength) ~= 1),
	warning('More than one wavelengths provided. Only first wavelength will be used.')
	wavelength = wavelength(1);
end;

exposure = nuanceautoexpose(handle.camera, handle.filter, wavelength);

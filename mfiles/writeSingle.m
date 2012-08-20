function writeSingle(im, name, wavelength, exposure)

if (nargin < 4),
	exposure = [];
end;
	

if (numel(wavelength) ~= 1),
	warning('More than one wavelengths provided. Only first wavelength will be used.')
	wavelength = wavelength(1);
end;

if (isempty(exposure)),
	imwrite(im, sprintf('%s_%d.tif', name, wavelength));
else
	if (numel(exposure) ~= 1),
		warning('More than one exposures provided. Only first exposure will be used.')
		exposure = exposure(1);
	end;
	imwrite(im, sprintf('%s_exp%gms_%d.tif', name, exposure, wavelength));
end;
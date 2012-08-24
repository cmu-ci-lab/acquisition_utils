function exposures = autoExposeCube(handle, wavelengths, singleExposure)

if ((nargin < 2) || isempty(wavelengths)),
	wavelengths = 420:10:720;
end;

if ((nargin < 3) || isempty(singleExposure)),
	singleExposure = true;
end;

exposures = nuanceautoexpose(handle.camera, handle.filter, wavelengths);
if (singleExposure == true),
	exposures = min(exposures);
end;

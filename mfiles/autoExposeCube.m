function exposures = autoExposeCube(handle, wavelengths, singleExposure)

if ((nargin < 3) || isempty(singleExposure)),
	singleExposure = true;
end;

exposures = nuanceautoexpose(handle.camera, handle.filter, wavelengths);
if (singleExposure == true),
	exposures = min(exposures);
end;
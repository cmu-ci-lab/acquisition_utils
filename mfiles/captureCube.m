function cube = captureCube(handle, wavelengths, exposures, singleExposure)

if ((nargin < 4) || isempty(singleExposure)),
	singleExposure = true;
end;

if ((nargin < 3) || isempty(exposures)),
	exposures = autoExposeCube(handle, wavelengths, singleExposure);
end;
	
numWavelengths = length(wavelengths);
if (length(exposures) == numWavelengths),
	cube = nuancecapture(handle.camera, handle.filter, wavelengths,...
						exposures);
else
	cube = nuancecapture(handle.camera, handle.filter, wavelengths,...
						exposures(1) * ones(size(wavelengths)));
end;
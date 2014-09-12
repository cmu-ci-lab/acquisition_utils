function cube = captureCube(handle, wavelengths, exposures, singleExposure)

if ((nargin < 2) || isempty(wavelengths)),
	wavelengths = 420:10:720;
end;

if ((nargin < 4) || isempty(singleExposure)),
	singleExposure = true;
end;

if ((nargin < 3) || isempty(exposures)),
	exposures = autoExposeCube(handle, wavelengths, singleExposure);
end;
	
numWavelengths = numel(wavelengths);
if (numel(exposures) == numWavelengths),
	cube = nuancecapture(handle.camera, handle.filter, wavelengths(:),...
						exposures(:));
else
	if (numel(exposures) ~= 1),
		warning('Number of exposures provided different than number of wavelengths and larger than one. Only first exposure will be used.');
		exposures = exposures(1);
	end;
	cube = nuancecapture(handle.camera, handle.filter, wavelengths(:),...
						exposures * ones(size(wavelengths)));
end;

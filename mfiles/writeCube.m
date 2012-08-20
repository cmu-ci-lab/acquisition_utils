function writeCube(cube, name, wavelengths, exposures)

if (nargin < 4),
	exposures = [];
end;
	
numWavelengths = numel(wavelengths);
if (isempty(exposures)),
	for iterWavelength = 1:numWavelengths,
		imwrite(cube(:, :, iterWavelength),...
			sprintf('%s_%d.tif', name, wavelengths(iterWavelength)));
	end;
elseif (numel(exposures) == numWavelengths),
	for iterWavelength = 1:numWavelengths,
		imwrite(cube(:, :, iterWavelength),...
			sprintf('%s_exp%gms_%d.tif', name,...
				exposures(iterWavelength),...
				wavelengths(iterWavelength)));
	end;
else
	if (numel(exposures) ~= 1),
		warning('Number of exposures provided different than number of wavelengths and larger than one. Only first exposure will be used.');
		exposures = exposures(1);
	end;
	for iterWavelength = 1:numWavelengths,
		imwrite(cube(:, :, iterWavelength),...
			sprintf('%s_exp%gms_%d.tif', name,...
				exposures,...
				wavelengths(iterWavelength)));
	end;
end;
% h = deviceopen;
exposures = 0.1 * 2.^(0:1:18);
numExposures = length(exposures);
wavelengths = 420:10:720;
numWavelengths = length(wavelengths);
HDRCube = cell(numWavelengths, 1);
for iterWave = 1:numWavelengths,
	HDRCube{iterWave} = captureHDRSingle(h, wavelengths(iterWave), exposures);
end;
% deviceclose(h);
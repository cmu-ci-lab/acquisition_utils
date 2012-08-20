function hdr = captureHDRSingle(handle, wavelength, exposures)
	
numExposures = length(exposures);
I = captureSingle(handle, wavelength, exposures(1));
hdr = zeros(size(I, 1), size(I, 2), numExposures, class(I));
hdr(:, :, 1) = I;
for iterExposure = 2:numExposures,
	hdr(:, :, iterExposure) = captureSingle(handle, wavelength,...
											exposures(iterExposure));
end;
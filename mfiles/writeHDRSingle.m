function writeHDRSingle(hdr, name, wavelength, exposures)

numExposures = length(exposures);
for iterExposure = 1:numExposures,
	writeSingle(hdr(:, :, iterExposure), name, wavelength,...
				exposures(iterExposure));
end;
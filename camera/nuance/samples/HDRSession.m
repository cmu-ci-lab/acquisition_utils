numShots = 10;
exposures = 0.1 * 2.^(0:1:16);
numExposures = length(exposures);

hdravg = zeros(1040, 1392, numExposures);
for iterShot = 1:numShots,
	hdr = captureHDRSingle(h, 530, exposures);
	hdravg = hdravg + double(hdr);
end;

hdr = uint16(hdravg / numShots);
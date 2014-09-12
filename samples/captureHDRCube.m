h = deviceopen;
% nuanceset(h.camera, 'binning', 1);
exposures = 0.1 * 2.^(0:1:19);
% exposures = 0.1 * 2.^(0:1:16);
numExposures = length(exposures);
wavelengths = [488 532 635];
% wavelengths = getNuanceWavelengths;
numWavelengths = length(wavelengths);
HDRCube = cell(numWavelengths, 1);
HDRIm = cell(numWavelengths, 1);
for iterWave = 1:numWavelengths,
	HDRCube{iterWave} = captureHDRSingle(h, wavelengths(iterWave), exposures);
end;
deviceclose(h);

%%
minVal = 15;
maxVal = 4080;
for iterWave = 1:numWavelengths,
	HDRIm{iterWave} = ldr2hdr_fisher(HDRCube{iterWave}, exposures, minVal, maxVal);
end;

%%
% nuanceWavelengths = getNuanceWavelengths;
% func = getCompensationFunction('nuance_sensitivity', nuanceWavelengths);
% inds = [find(nuanceWavelengths == 490) find(nuanceWavelengths == 530) find(nuanceWavelengths == 630)];
% for iterWave = 1:numWavelengths,
% 	HDRIm{iterWave} = HDRIm{iterWave} / func(iterWave);
% end;
% 
% %%
% exposure = 100;
% figure; imshow(exposure * HDRIm{1}/4095, []); impixelinfo
% figure; imshow(exposure * HDRIm{2}/4095, []); impixelinfo
% figure; imshow(exposure * HDRIm{3}/4095, []); impixelinfo
% 
% %%
% exposure = 1;
% figure; imshow(cbrt(exposure * HDRIm{1}/4095)); impixelinfo
% figure; imshow(cbrt(exposure * HDRIm{2}/4095)); impixelinfo
% figure; imshow(cbrt(exposure * HDRIm{3}/4095)); impixelinfo
% 
% %%
% coord = [703, 590];
% im = HDRIm{1}; figure; plot(im(:, coord(1))); figure; plot(im(coord(2), :));
% im = HDRIm{2}; figure; plot(im(:, coord(1))); figure; plot(im(coord(2), :));
% im = HDRIm{3}; figure; plot(im(:, coord(1))); figure; plot(im(coord(2), :));
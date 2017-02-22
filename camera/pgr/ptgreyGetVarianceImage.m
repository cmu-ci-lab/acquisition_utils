function [varianceImage, meanImage, frame] = ptgreyGetVarianceImage(vid, numFrames)

frame = getsnapshot(vid);
meanImage = double(frame) / 4095;
meanSqImage = (double(frame) / 4095) .^ 2;
for iter = 2:numFrames,
	frame = getsnapshot(vid);
	meanImage = meanImage + double(frame) / 4095;
	meanSqImage = meanSqImage + (double(frame) / 4095) .^ 2;
end;
meanImage = meanImage / numFrames;
meanSqImage = meanSqImage / numFrames;
varianceImage = meanSqImage - meanImage .^ 2;
function src = avtpreview(vid, src, binning)

if ((nargin < 3) || (isempty(binning))),
	binning = 4;
end;

src = avtbinning(src, binning);
src.AcquisitionFrameRateAbs = 10;
h = preview(vid);
hold(ancestor(h, 'axes'), 'on');
im = getsnapshot(vid);
plot(floor(size(im, 2) / 2), floor(size(im , 1) / 2), 'rX', 'MarkerSize', 40, 'Parent', ancestor(h, 'axes'));
plot(floor(size(im, 2) / 2), floor(size(im , 1) / 2), 'b.', 'MarkerSize', 40, 'Parent', ancestor(h, 'axes'));
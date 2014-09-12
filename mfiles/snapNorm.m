function im = snapNorm(handle, maxVal)

if ((nargin < 2) || isempty(maxVal)),
	maxVal = 4095;
end;

im = snap(handle);
im = double(im) / maxVal;
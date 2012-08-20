function writeFullCube(cube, name, varargin)

wavelengths = 420:10:720;
writeCube(cube, name, wavelengths, varargin{:});
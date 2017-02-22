function vid = avtsetroi(vid, tx, ty)

resolution = vid.VideoResolution;
if ((nargin <= 1) || isempty(tx)),
    tx = [1 resolution(1)];
end;
    
if ((nargin <= 2) || isempty(ty)),
    ty = [1 resolution(2)];
end;

tx = round(tx);
ty = round(ty);
vid.ROIPosition = [(tx(1) - 1), (ty(1) - 1), (tx(2) - tx(1) + 1), (ty(2) - ty(1) + 1)];

function im = snap(handle)

im = imflip(nuancesnap(handle.camera)');

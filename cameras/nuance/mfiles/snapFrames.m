function frames = snapFrames(handle, numFrames)

frames = imflip(permute(nuancesnapframes(handle.camera, numFrames), [2 1 3]));

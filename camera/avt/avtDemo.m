vid = videoinput('gige', 1, 'Mono14');
src = getselectedsource(vid);
vid.FramesPerTrigger = 1;
preview(vid);
src.ExposureTimeAbs = 10000;
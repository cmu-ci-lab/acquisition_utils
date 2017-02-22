function [vid, src] = ptgreyopen
vid = videoinput('dcam', 1, 'Y8_640x480');
src = getselectedsource(vid);

vid.FramesPerTrigger = 1;

src.AutoExposureControl = 'absolute';

src.BrightnessControl = 'absolute';

src.GainControl = 'absolute';

src.SaturationControl = 'absolute';

src.ShutterControl = 'absolute';

src.TriggerDelayControl = 'absolute';
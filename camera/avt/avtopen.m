function [vid, src] = avtopen

vid = videoinput('gige', 1, 'Mono14');
src = getselectedsource(vid);
vid.FramesPerTrigger = 1;
% vid.Timeout = 10;
% src.PacketSize = 8000;
% src.PacketDelay = 72098;
src.BinningHorizontal = 1;
src.BinningVertical = 1;
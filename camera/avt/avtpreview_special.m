figure;
while(true),
    im = getsnapshot(vid);
    subplot(1, 2, 1); plot(im(:, floor(end/2)));
    subplot(1, 2, 2); plot(im(floor(end/2), :));
end;
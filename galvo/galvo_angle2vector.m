function vector = galvo_angle2vector(angle)

angle = angle.*2;

normal = [0 0 1]';

theta = angle(2).*(2.*pi./360);
R_x = [1  0          0;          ...
       0  cos(theta) sin(theta); ...
       0 -sin(theta) cos(theta)];
   
theta = angle(1).*(2.*pi./360);
R_y = [cos(theta) 0 sin(theta); ...
       0          1 0;          ...
      -sin(theta) 0 cos(theta)];
   
vector = R_x*R_y*normal;

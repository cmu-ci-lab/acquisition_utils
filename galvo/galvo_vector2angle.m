function angle = galvo_vector2angle(vector)

angle = [0 0];

vector = vector./norm(vector);

angle(2) = atan2(vector(2),vector(3)).*360./(2.*pi);

theta = angle(2).*(2.*pi./360);
R_x = [1  0          0;          ...
       0  cos(theta) sin(theta); ...
       0 -sin(theta) cos(theta)];
vector = R_x'*vector;

angle(1) = atan2(vector(1),vector(3)).*360./(2.*pi);

angle = angle./2;

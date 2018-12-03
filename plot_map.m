in = dlmread('map.dat');
num = length(in(:,3));
map = reshape(in(:,3),[sqrt(num),sqrt(num)]);
x = [-700:10:700];
contour(x,x,map)
hold on
surf(x,x,map-max(max(map)))
material shiny
shading interp
hold off

in = dlmread('res_map.dat');
x = in(:,1);
y = in(:,2);
num = length(x);
nn = sqrt(num);
x_min = min(x);
y_min = min(y);
x_max = max(x);
y_max = max(y);
x = linspace(x_min,x_max,nn);
y = linspace(y_min,y_max,nn);

n_res = size(in)
n_res = n_res(2)

for i = 3:n_res
	map = reshape(in(:,i),[nn,nn]);
	%{
	surf(x,y,map);
	shading interp;
	camlight
	lighting gouraud
	%}
	contour(x,y,map)
	pause
end

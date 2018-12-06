in = dlmread('ss.dat');
x = in(:,1);
y = in(:,2);
gen = in(:,3);
frame=12;

x_max = max(x);
x_min = min(x);
y_max = max(y);
y_min = min(y);
num = max(gen);

for i=0:num
	scatter(x(gen==i),y(gen==i));
	xlim([x_min,x_max])
	ylim([y_min,y_max])
%	xlim([-100,600])
%	ylim([-700,0])
	pause(1/frame)
end

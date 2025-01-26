%This code will create a 3D plot for a multi-variable function
clc;clear;

%m represents the number of x-values, n represents the number of y-values.
m = 401; n = 301;

%Poly_xy is the function we are plotting.
poly_xy = @(x,y) 2*x.^2 + 3*x.*y + 6*y.^2 + 7*x - 5*y + 10;
%create vectors for x and y-values.
x = linspace(-4,-1,m);
y = linspace(0,2,n);

%Use the fOnGrid function to create a vector of function values.
fVals = fOnGrid(x,y,poly_xy);

%Plot the function.
figure(1); clf;
surf(x,y,fVals);
view(64.50,16.00);colormap(jet);
xlabel('x'); ylabel('y'); title('poly xy');
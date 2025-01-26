%This code will create a contour plot for a 3D polynomial
%To use this code, you must have the function fOnGrid.
clc;clear;

%m refers to the number of x values, n refers to number of y values.
m = 401; n = 301;

%poly_xy represents the function.M
poly_xy = @(x,y) 2*x.^2 + 3*x.*y + 6*y.^2 + 7*x - 5*y + 10;
%create a vector of x and y values.
x = linspace(-4,-1,m);
y = linspace(0,2,n);

%using the function fOnGrid, we will be able to get the function values.
fVals = fOnGrid(x,y,poly_xy);

%Plot the contour lines.
figure(1); clf;
contour(x,y,fVals,20);
xlabel('x'); ylabel('y'); title('20 contour lines for poly_xy(x, y).');
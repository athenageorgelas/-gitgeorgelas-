%Comparison of two curves
clc; clear;

%Input the number of points on the graph (larger N produces a smoother curve.)
N = input('Enter a positive N: ');

%Create x vector with values between -3 and 3, equal space, N entries
x = linspace(-3,3,N);

%Calculate the f(x) and g(x) functions
yf = ( cos(6*x) .* exp((-1/3)*x) )./( 1 + 2*(x.^2) + x.^4 );

yg = ( cos(3*x) .* exp((-1/3)*x) )./( 2 + 2*(x.^2) + x.^4 );

%Plot the curves
figure(1); clf;
plot(x,yf,'-r', LineWidth = 1.5);
hold on
plot(x,yg,'--b',LineWidth = 1.5);
xlabel('x'), ylabel('y')
title('A comparison of f(x) and g(x)')
legend('Function f(x)', 'Function g(x)')

%Save a PDF and a figure of the plot created.
filename = 'Compare_Curves.pdf';
saveas(gcf,'Compare_Curves.pdf');
saveas(gcf,'Compare_Curves.fig');

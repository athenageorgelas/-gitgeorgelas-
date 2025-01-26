function fVals = fOnGrid(x,y,f)
% x is a 1-by-n vector
% y is a 1-by-m vector
% f is a function handle that identifies a function of two variables.
% fVals is an m-by-n matrix where fVals(i,j) = f(x(j),y(i)).

n = length(x); m = length(y); 
fVals = zeros(m,n);
for j=1:n
    for i = 1:m
        fVals(i,j) = f(x(j),y(i));
    end
end
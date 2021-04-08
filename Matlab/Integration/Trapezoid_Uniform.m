% A solution for electronic problem 5.1.1.

% A function to apply the trapezoid method to a function f over an interval
% [a,b] with n uniform subintervals, and outputs the integral
% approximation.
function sum = Trapezoid_Uniform(f, a, b, n)
    % Step size
    h = (b-a)/n;
    
    % Add endpoints
    sum = (f(a)+f(b))/2;
    
    % Add the interval points
    for i=1:n-1
        x = a+i*h;
        sum = sum + f(x);
    end
    
    % Multiply by h and return sum
    sum = sum*h;
end
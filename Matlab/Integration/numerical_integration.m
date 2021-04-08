% A solution for electronic problem 5.1.5.b.

format short;
format compact;
clc;            % Formatting and clearing screen

% Estimate using trapezoid method
estimate = Trapezoid_Uniform(@f, .01, 100, 60)

% Approximate integral evaluation
actual = integral(@func, 1000, .01)

% True value pi/2
pi/2

% Function f(x) = sin(x)/x
function y = f(x)
    y = sin(x)./x;
end

% Function f(x) = -sin(1/t)/t found by substituting x=1/t into f(x)
function y = func(x)
    y = -sin(1./x)./x;
end
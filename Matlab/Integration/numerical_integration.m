% A solution for electronic problem 5.1.5.b.

format short;
format compact;
clc;            % Formatting and clearing screen

% Estimate using trapezoid method
estimate = Trapezoid_Uniform(@f, .01, 100, 60)

% Approximate integral evaluation
actual = integral(@f, 0, 1000)

% True value pi/2
pi/2

% Function f(x) = sin(x)/x
function y = f(x)
    y = sin(x)./x;
end

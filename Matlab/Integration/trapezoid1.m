% A solution for electronic problem 5.1.2.a.

format short;
format compact;
clc;

% Start and endpoints
a = 0;
b = pi;

% True value of the integral
true = integral(@f, a, b);

% Integral estimate with trapezoid method
estimate = Trapezoid_Uniform(@f, a, b, 60);

% Display output
output = [estimate, true, abs(true-estimate)];
Integral_Table = array2table(output, 'VariableNames', {'Trapezoid', 'Integral', 'Error'})

% Function f(x) = sin(x)
function y = f(x)
    y = sin(x);
end
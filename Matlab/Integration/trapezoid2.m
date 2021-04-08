% A solution for electronic problem 5.1.2.b.

format short;
format compact;
clc;            % Formatting and clearing screen

% Start and endpoints
a = 0;
b = 1;

% True value of integral
true = integral(@f, a, b);

% Integral estimate with trapezoid method
estimate = Trapezoid_Uniform(@f, a, b, 60);

% Display output
output = [estimate, true, abs(true-estimate)];
Integral_Table = array2table(output, 'VariableNames', {'Trapezoid', 'Integral', 'Error'})

% Function f(x) = e^x
function y = f(x)
    y = exp(x);
end
% A solution for electronic problem 4.2.1.

format short;   % Formatting
format compact;
clc;            % Clear console for clean output

% Array of equally spaced nodes for interpolation
x = linspace(-5, 5, 21);
% Function values at node points
y = func(x);

% Calculate coefficients of interpolating polynomial
a = coef(x, y);

% Values to calculate error at
nodes = linspace(-5, 5, 41);

% Compare function to interpolating polynomial
output = [];
for i=1:41
    f = func(nodes(i));
    p = eval(x, a, nodes(i));
    output = [output; nodes(i), f, p, abs(f-p)];
end
Error_Table = array2table(output, 'VariableNames', {'x', 'f(x)', 'p(x)', 'error'})

% Function for f(x) = (x^2 + 1)^-1
function f = func(x)
    f = (x.^2 + 1).^-1;
end

% Function to calculate interpolating polynomial coefficients
function [a] = coef(x, y)
    a = y;
    for j=1:20
        for i=20:-1:j
            a(i+1) = ( (a(i+1) - a(i)) / (x(i+1) - x(i-j+1)) );
        end
    end
end

% Function to find value of interpolating polynomial at point t
function pn = eval(x, a, t)
    temp = a(21);
    for i=20:-1:1
        temp = temp*(t - x(i)) + a(i);
    end
    pn = temp;
end
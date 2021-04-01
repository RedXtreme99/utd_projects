% A solution for electronic problem 4.2.2.

format short;   % Formatting
format compact;
clc;            % Clear console for clean output

% Arrays of Chebyshev nodes for interpolation
i = 0:20;
x1 = 5*cos(i*pi/20);
x2 = 5*cos((2*i+1)*pi/42);

% Function values at node points
y1 = func(x1);
y2 = func(x2);

% Calculate coefficients of interpolating polynomial
a1 = coef(x1, y1);
a2 = coef(x2, y2);

% Values to calculate error at
nodes = linspace(-5,5,41);

% Compare function to interpolating polynomial from first set of Chebyshev
% nodes
output = [];
for i=1:41
    f = func(nodes(i));
    p = eval(x1, a1, nodes(i));
    output = [output; nodes(i), f, p, abs(f-p)];
end
Error_Table_1 = array2table(output, 'VariableNames', {'x', 'f(x)', 'p(x)', 'error'})

% Compare function to interpolating polynomial from second set of Chebyshev
% nodes
output = [];
for i=1:41
    f = func(nodes(i));
    p = eval(x2, a2, nodes(i));
    output = [output; nodes(i), f, p, abs(f-p)]; 
end
Error_Table_2 = array2table(output, 'VariableNames', {'x', 'f(x)', 'p(x)', 'error'})

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
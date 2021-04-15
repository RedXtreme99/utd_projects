% A solution for electronic problem 5.3.1.

format short;
format compact;
clc;            % Formatting and clearing screen

% Use recursive Simpson's rule to approximate integral of f from 0 to 1
[integral1, p1] = simpson(@f, 0, 1, .000005, 0, 4);
integral1
% Use recursive Simpson's rule to approximate integral of g from 0 to 1/sqrt(2)
[integral2, p2] = simpson(@g, 0, 1/sqrt(2), .000005, 0, 4);
integral2

% Plot f and the partition points used for Simpson's
tiledlayout(2,1);
nexttile;
plot(linspace(0,1), arrayfun(@f, linspace(0,1)), 'b');
hold on;
title('f(x) = $\frac{4}{1+x^2}$', 'Interpreter', 'latex', 'FontSize', 20);
stem(unique(p1), arrayfun(@f, unique(p1)), ':k');
hold off;

% Plot g and the partition points used for Simpson's
nexttile;
plot(linspace(0, 1/sqrt(2)), arrayfun(@g, linspace(0, 1/sqrt(2))), 'b');
hold on;
title('g(x) = $8(\sqrt{1-x^2}-x)$', 'Interpreter', 'latex', 'FontSize', 20);
stem(unique(p2), arrayfun(@g, unique(p2)), ':k');
hold off;

% Recursive Simpson's rule, returns the approximation of the integral and
% the partition points. Takes as input a function, interval start a,
% interval end b, an error tolerance epsilon, the current recursive level,
% and the max recursive level
function [simpson_result, partition] = simpson(f, a, b, eps, level, level_max)
    % Initial partition interval
    partition = [a, b];
    
    % Calculate one and two simpson calculations
    level = level + 1;
    h = b - a;
    c = (a + b) / 2;
    one_simpson = h * (f(a) + 4*f(c) + f(b)) / 6;
    d = (a + c) / 2;
    e = (b + c) / 2;
    two_simpson = h * (f(a) + 4*f(d) + 2*f(c) + 4*f(e) + f(b)) / 12;
    partition = [partition, c, d, e];
    
    % Base case, max iterations or simpsons are accurate enough
    if level >= level_max
        simpson_result = two_simpson;
    else
        if abs(two_simpson - one_simpson) < 15*eps
            simpson_result = two_simpson + (two_simpson - one_simpson)/15;
    % Recursive calls on left and right partitions
        else
            [left_simpson, left_p] = simpson(f, a, c, eps/2, level, level_max);
            [right_simpson, right_p] = simpson(f, c, b, eps/2, level, level_max);
            simpson_result = left_simpson + right_simpson;
            partition = [partition, left_p, right_p];
        end
    end
end

function y = f(x)
    y = 4 / (x.^2 + 1);
end

function y = g(x)
    y = 8 * ((1 - x.^2).^(1/2) - x);
end
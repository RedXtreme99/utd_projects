% A solution for electronic problem 3.2.2.

format short;   % formatting
format compact;
clc;            % clear console for clean output

newtons(2, 10, .000005, .0001);     % Call to Newton's method on the function for x=2

% Function for f(x) = x^3 + 2x^2 + 10x - 20 to find root using Newton's method
function f = func(x)
    f = x.^3 + 2*x.^2 + 10*x - 20;
end

% Function for f'(x) = 3x^2 + 4x + 10 to find root
function fprime = deriv(x)
    fprime = 3*x.^2 + 4*x + 10;
end

% Function to calculate Newton's method for a given function, takes an
% intial point x, a number of iterations, epsilon to check for when a root
% is found, and a sigma to determine that the derivative is not 0.
function root = newtons(x, nmax, eps, sigma)
    fx = func(x);
    output = [0,x,fx];
    for n=1:nmax
        fp = deriv(x);
        if abs(fp) < sigma
            disp('Derivative too close to 0');
            return
        end
        % Apply Newton's Method, x1 = x0 - f(x0)/f'(x0)
        d = fx/fp;
        x = x - d;
        fx = func(x);
        output = [output; n, x, fx];
        if abs(d) < eps
            T = array2table(output, 'VariableNames', {'Iteration', 'x', 'f(x)'})
            root = x
            return
        end
    end
    disp('Root not found in nmax iterations');
end
% A solution for electronic problem 3.2.15.

format short;   % formatting
format compact;
clc;            % clear console for clean output

newtons(1, 30, .000005, .0001);     % Call to Newton's method on the function for x=1

% Function for f(x) = .5x^2 + x + 1 - e^x to find root using Newton's method
function f = func(x)
    f = .5*x.^2 + x + 1 - exp(x);
end

% Function for f'(x) = x + 1 - e^x to find root
function fprime = deriv(x)
    fprime = x + 1 - exp(x);
end

% Function to calculate Newton's method for a given function, takes an
% intial point x, a number of iterations, epsilon to check for when a root
% is found, and a sigma to determine that the derivative is not 0.
function root = newtons(x, nmax, eps, sigma)
    fx = func(x);
    output = [0,x,fx];
    for n=1:nmax
        fp = deriv(x);
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
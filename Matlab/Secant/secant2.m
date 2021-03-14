% A solution for electronic problem 3.3.6.b.

format short;   % formatting
format compact;
clc;            % clear console for clean output

x0 = .5;
newtons(x0, 10, .000005, .0001);     % Call to Newton's method
x1 = x0 - func(x0)/deriv(x0);
secant(x0, x1, 10, .000005);         % Call to secant method

% Function for f(x) = x^3 - 2sinx
function f = func(x)
    f = x.^3 - 2*sin(x);
end

% Function for f'(x) = 3x^2 - 2cosx
function fprime = deriv(x)
    fprime = 3*x.^2 - 2*cos(x);
end

% Function to calculate Newton's method for a given function, takes an
% intial point x, a number of iterations, epsilon to check for when a root
% is found, and a sigma to determine that the derivative is not 0.
function rootn = newtons(x, nmax, eps, sigma)
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
            Newtons_Output_b = array2table(output, 'VariableNames', {'Iteration', 'x', 'f(x)'})
            rootn = x
            return
        end
    end
    disp('Root not found in nmax iterations');
end

% Function to calculate secant method for a given function, takes two initial
% points, a max number of iterations, and an epsilon as inputs.
function roots = secant(x0, x1, nmax, eps)
    fx0 = func(x0);
    fx1 = func(x1);
    if fx0 > fx1
        tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = fx0;
        fx0 = fx1;
        fx1 = tmp;
    end
    output = [0, x0, fx0; 1, x1, fx1];
    for n=2:nmax
        % Apply secant method, x2 = x1 - (x1-x0)/(f(x1)-f(x0)) * f(x1)
        d = (x1-x0)/(fx1-fx0);
        x2 = x1 - d*fx1;
        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = func(x1);
        output = [output; n, x0, fx0];        
        if abs(x1-x0) < eps
            Secant_Output_a = array2table(output, 'VariableNames', {'Iteration', 'x', 'f(x)'})
            roots = x1
            return
        end
    end
    disp('Root not found in nmax iterations');
    Secant_Output_a = array2table(output, 'VariableNames', {'Iteration', 'x', 'f(x)'})
end
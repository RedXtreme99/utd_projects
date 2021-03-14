% A solution for electronic problem 3.3.10.

format short;   % formatting
format compact;
clc;            % clear console for clean output

% Print the true root of 0 and the target ratio -1/2 f"(r)/f'(r)
root = 0
target = -.5*deriv2(root)/deriv(root)
secant(.25, .5, 10, .000005);         % Call to secant method

% Function for f(x) = arctan(x)
function f = func(x)
    f = atan(x);
end

% Function for f'(x) = 1/(x^2+1)
function fp = deriv(x)
    fp = 1/(1+x.^2);
end

% Function for f"(x) = -2x/(x^2+1)^2
function fpp = deriv2(x)
    fpp = -2*x / (x.^2 + 1).^2;
end

% Function to calculate secant method for a given function, takes two initial
% points, a max number of iterations, and an epsilon as inputs.
function roots = secant(x0, x1, nmax, eps)
    r = 0;
    fx0 = func(x0);
    fx1 = func(x1);
    e0 = x0 - r;
    e1 = x1 - r;
    output = [];
    for n=2:nmax
        % Apply secant method, x2 = x1 - (x1-x0)/(f(x1)-f(x0)) * f(x1)
        d = (x1-x0)/(fx1-fx0);
        x2 = x1 - d*fx1;
        e2 = x2 - r;
        output = [output; n, x2, e2/(e1*e0) ];
        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = func(x1);
        e0 = e1;
        e1 = e2;
        if abs(x1-x0) < eps
            Error_Ratio = array2table(output, 'VariableNames', {'Iteration', 'Root', 'Error Ratio'} )
            roots = x1
            return
        end
    end
    disp('Root not found in nmax iterations');
    Error_Ratio = array2table(output)
end

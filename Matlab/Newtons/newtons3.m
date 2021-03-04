% A solution for electronic problem 3.2.18.

format short;   % formatting
format compact;
clc;            % clear console for clean output

epsilon = .000005;
x0 = bisection(1,2,30, epsilon)     % Call to bisection to find x0
newtons(x0, 10, epsilon, .0001);     % Call to Newton's method

% Function for f(x) = 2x/(1+x^2) - arctan(x) to find x0 using bisection
function f1 = func1(x)
    f1 = 2*x/(1+x.^2) - atan(x);
end

% Function for f(x) = arctan(x) for Newton's method
function f = func(x)
    f = atan(x);
end

% Function for f'(x) = 1/(1+x^2) to find root
function fprime = deriv(x)
    fprime = 1/(1+x.^2);
end

% Bisection function, finds a root between a and b if one exists
% Takes input interval [a,b], a max number of iterations, and an acceptable
% error threshold.
function root = bisection(a, b, nmax, eps)
    % Determine if a root exists by calculating the value of the function
    % at the endpoints and checking if their signs are different, if not
    % then there is no root
   fa = func1(a);
   fb = func1(b);
   if sign(fa) == sign(fb)
       output = [a,b,fa,fb]
       disp('The function has the same sign at a and b,so there is no root between them');
       return
   end
   % Iteratively halve the interval and check which side the root is on
   % until we have determined the root
   error = b - a;
   for n=0:nmax
       error = error/2;
       c = a + error;
       fc = func1(c);
       if abs(error) < eps
           disp('Root found');
           root = c;
           return
       end
       if sign(fa) ~= sign(fc)
           b = c;
           fb = fc;
       else
           a = c;
           fa = fc;
       end
   end
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
    T = array2table(output, 'VariableNames', {'Iteration', 'x', 'f(x)'})
end
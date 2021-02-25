% A solution for electronic problem 3.1.3.

format short;   % Format numbers to be compact
clc;            % Clear console for clean output

bisection(4,5,30,.0000001); % Bisection for interval [4,5]
bisection(1,2,30,.0000001); % Bisection for interval [1,2]

% Function x = tan(x)
% Rewritten as x - tan(x) = 0, and then multiplied by cos(x)
% to get xcos(x) - sin(x) to get a continuous curve for bisection
function f = func(x)
    f = x*cos(x) - sin(x);
end

% Bisection function, finds a root between a and b if one exists
% Takes input interval [a,b], a max number of iterations, and an acceptable
% error threshold.
function root = bisection(a, b, nmax, eps)
    % Determine if a root exists by calculating the value of the function
    % at the endpoints and checking if their signs are different, if not
    % then there is no root
   fa = func(a);
   fb = func(b);
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
       fc = func(c);
       if abs(error) < eps
           disp('Root found');
           root = c
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
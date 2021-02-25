% A solution for computer problem 1.4.6.

format long; % Format output to be show full precision

% Tabular output that prints the value of x, then the recomputed and
% original function values for x, and the difference between them
disp('         x              new                 original                  error')

x = [0, .000001, .0001, .001, .1, pi/6, pi/4]; % Array of x values to test
for i=1:7
    output = [x(i), func(x(i)), original(x(i)), abs(original(x(i)) - func(x(i)))];
    disp(output);
    disp(' ');
end

% Recomputed function to avoid cos(x)-1 to preserver precision near x=0
function f = func(x)
    f = sin(x) - 2*(sin(x/2)).^2;
end

% Original function that has loss of precision near x=0
function f = original(x)
    f = sin(x) - 1 + cos(x);
end
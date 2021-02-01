% A solution for electronic problem 1.1.1.

format shortG;  % Format output to be tabular
format compact; % Format output to be single-spaced

clc;            % Clears console window for clean output

n = 30;         % Number of iterations
x = .5;         % x-value where derivative is being evaluated
h = 1;          % Step value of h, will approach 0
emin = 1;       % Variable to store minimum error

% Print table column headers
disp('          i             h           y         error');

for i=1:n
    h = 0.25 * h;
    y = (sin(x+h) - sin(x)) / h;
    error = abs(cos(x) - y);

    %  ouput vector with i, h, y, and error
    output = [i, h, y, error];
    disp(output);
    if (error < emin)
        emin = error;
        imin = i;
    end
end

% Display minimum error and corresponding iteration
disp('imin is'); disp(imin);
disp('emin is'); disp(emin);
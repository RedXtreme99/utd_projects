% A solution for electronic problem 2.3.5.

format compact;
format short;
clc;            % Format and clear screen

% Initialize b
b = ones(100,1) * 40;
b(1) = -20;
b(100) = -20;

% Initialize the diagonal
d = ones(100,1) * -4;
d(1) = 4;
d(100) = 4;

% Initialize sub-diagonal
a = ones(99,1);
a(99) = -1;

% Initialize super-diagonal
c = ones(99,1);
c(1) = -1;

% Calculate the matrix M and the true solution to the system
M = diag(d) + diag(a,-1) + diag(c,1);
true = linsolve(M, b);

% Calculate the solution using Tri
x = Tri(a, d, c, b);

% Print output in table
output = [];
for i=1:100
    output = [output; true(i) x(i)];
end
table = array2table(output)

% Function Tri that takes subdiagonal a, diagonal d, superdiagonal c, and
% system solution b as inputs, and stores the output in x.
function b = Tri(a, d, c, b)
    n = length(b);
    
    % Forward and backward elimination
    for i=2:n
        xmult = a(i-1) / d(i-1);
        d(i) = d(i) - xmult * c(i-1);
        b(i) = b(i) - xmult * b(i-1);
    end
    
    % Store solution in place in b
    b(n) = b(n) / d(n);
    for i=n-1:-1:1
        b(i) = (b(i) - c(i) * b(i+1)) / d(i);
    end
end
% A solution for electronic problem 2.3.1.

format compact;
format short;
clc;            % Format and clear screen

% Testing for non-symmetric matrix M
c = [1, 1];
d = [4, 4, 4];
a = [1, 2];
M = diag(d) + diag(c,1) + diag(a,-1);

% Solution x
x = [1, 1, 1]
% Let b be the solution to Mx=b, and then use it in Tri to generate the
% solution in place
b = transpose(M*x');
b = Tri(a, d, c, b)

% Testing for symmetric matrix M
M(3,2) = 1;
b = transpose(M*x');
b = Tri(c, d, c, b)

% Function Tri that takes subdiagonal a, diagonal d, superdiagonal c, and
% system solution b as inputs, and stores the output in b.
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
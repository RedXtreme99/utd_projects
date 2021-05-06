% A solution for electronic problem 8.1.8.

format compact;
format short;
clc;            % Format and clear screen

% Solve system AX=B where A is nxn, X is nxn, and B is nxn identity matrix
% to solve for X = A inverse

% Initialize A as given
A = [-.0001, 5.096, 5.101, 1.853; 0, 3.737, 3.74, 3.392; 0, 0, .006, 5.254; 0, 0, 0, 4.567];
% Set B = I
B = eye(4);
% Solve the system for each column of B
[U, l] = Gauss(A);
X = zeros(size(B));
for i=1:size(B,2)
    X(:,i) = Solve(U, l, B(:,i));
end
disp(table(X, X-A\B, 'VariableNames',{'X', 'Error'}))
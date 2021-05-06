% A solution for electronic problem 8.1.5.

format compact;
format short;
clc;            % Format and clear screen

% Solve system AX=B where A is nxn, X is mxn, and B is mxn for unknown
% matrix X. Using different cases to test solution.

% Let B = I and solve using a known A to determine if X = A inverse
A = [1, 2, -1; -2, 0 ,1; 1, -1, 0];
B = eye(3);
% Solve the system for each column of B
[U, l] = Gauss(A);
X = zeros(size(B));
for i=1:size(B,2)
    X(:,i) = Solve(U, l, B(:,i));
end
disp(table(A, B, X, X-A\B, 'VariableNames',{'A', 'B', 'X', 'Error'}))

% Case A 3x3, B 3x2
A = randi(10, [3,3]);
B = randi(10, [3,2]);
% Solve the system for each column of B
[U, l] = Gauss(A);
X = zeros(size(B));
for i=1:size(B,2)
    X(:,i) = Solve(U, l, B(:,i));
end
disp(table(A, B, X, X-A\B, 'VariableNames',{'A', 'B', 'X', 'Error'}))

% Case A 3x3, B 3x4
A = randi(10, [3,3]);
B = randi(10, [3,4]);
% Solve the system for each column of B
[U, l] = Gauss(A);
X = zeros(size(B));
for i=1:size(B,2)
    X(:,i) = Solve(U, l, B(:,i));
end
disp(table(A, B, X, X-A\B, 'VariableNames',{'A', 'B', 'X', 'Error'}))
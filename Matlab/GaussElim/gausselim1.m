% A solution for electronic problem 2.1.3.

format compact;
format short;
clc;            % Format and clear screen

n = 10;         % Can be changed

% Initialize A to A[i,j] = i+j
A = zeros(n);
for i=1:n
    for j=1:n
        A(i,j) = i+j;
    end
end

% Initialize b to b(i) = i+1
b = zeros(n,1);
for i=1:n
    b(i) = i+1;
end

% Solve Ax=b
x = Naive_Gauss(A,b)
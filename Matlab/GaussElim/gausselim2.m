% A solution for electronic problem 2.1.8.

format compact;
format short;
clc;            % Format and clear screen

n = 10;         % Can be changed

% Initialize A to random values
A = rand(n);

% Initialize b to satisfy Ax = b such that x[j] = j
b = zeros(n,1);
for i=1:n
    for j=1:n
        b(i) = b(i) + A(i,j)*j;
    end
end

% Test solution, expect x[i] = i
x = Naive_Gauss(A,b)
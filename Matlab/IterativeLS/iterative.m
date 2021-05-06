% A solution to electronic problem 8.4.3.

format compact;
format short;
clc;            % Format and clear screen

% Initialize A and b
A = [7, 3, -1, 2; 3, 8, 1, -4; -1, 1, 4, -1; 2, -4, -1, 6];
b = [-1, 0, -3, 1];
n = length(b);
% Set initial guess for x to 0 vector
x_init= zeros(1,n);

% Find solution using Jacobi method
[x,k] = Jacobi(A, b, x_init)
% Find solution using Gauss-Seidel
[x,k] = GaussSeidel(A, b, x_init)
% Find solution using SOR
[x,k] = SOR(A, b, x_init, 1.4)
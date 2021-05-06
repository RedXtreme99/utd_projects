% A solution to electronic problem 8.4.4.

format compact;
format short;
clc;            % Format and clear screen

% Initialize A and b
A = [7, 3, -1, 2; 3, 8, 1, -4; -1, 1, 4, -1; 2, -4, -1, 6];
b = [-1, 0, -3, 1];
n = length(b);
% Set initial guess for x to 0 vector
x_init= zeros(1,n);

% Set each omega weight we will evaluate SOR at. omega = 1 is Gauss-Seidel
omega = [1, 1.2, 1.4, 1.6, 1.8];

% Determine number of iterations for each weight
k = zeros(1, length(omega));
for i=1:length(omega)
    [x,k(i)] = SOR(A, b, x_init, omega(i));
end

% Display results
disp(table(omega', k', 'VariableNames', {'Omega', 'Iterations'}));

% Plot omega weights versus number of iterations to convergence
scatter(omega, k, 100, 'filled');
title('SOR $\omega$ vs Iterations to Convergence', 'Interpreter', 'latex', 'FontSize', 20);
xlabel('$\omega$', 'Interpreter', 'latex');
ylabel('Number of Iterations');

% A solution for electronic problem 2.2.3.

format compact;
format short;
clc;            % Format and clear screen

% Matrix A
A = [.4096, .1234, .3678, .2943;
     .2246, .3872, .4015, .1129;
     .3645, .1920, .3781, .0643;
     .1784, .4002, .2786, .3927];
 
% Matrix Anew with updated value
Anew = [.4096, .1234, .3678, .2943;
     .2246, .3872, .4015, .1129;
     .3345, .1920, .3781, .0643;
     .1784, .4002, .2786, .3927];

% Target vector b
b = [.4043, .1550, .4240, .2557]';

% Apply Gaussian elimination with scaled partial pivoting and solve system
[A, l] = Gauss(A);
x = Solve(A, l, b)
[Anew, l] = Gauss(Anew);
xnew = Solve(Anew, l, b)
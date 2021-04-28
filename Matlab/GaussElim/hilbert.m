% A solution for electronic problem 3.2.4.

format compact;
format short;
clc;            % Format and clear screen

% Hilbert matrix system for n = 2
n = 2;
A = zeros(n);
b = zeros(n,1);
for i=1:n
    for j=1:n
        A(i,j) = 1 / (i + j - 1);
    end
end
for i=1:n
    sum = 0;
    for j=1:n
        sum = sum + A(i,j);
    end
    b(i) = sum;
end
[A, l] = Gauss(A);
x2 = Solve(A, l, b)

% Hilbert matrix system for n = 6
n = 6;
A = zeros(n);
b = zeros(n,1);
for i=1:n
    for j=1:n
        A(i,j) = 1 / (i + j - 1);
    end
end
for i=1:n
    sum = 0;
    for j=1:n
        sum = sum + A(i,j);
    end
    b(i) = sum;
end
[A, l] = Gauss(A);
x6 = Solve(A, l, b)

% Hilbert matrix system for n = 10
n = 10;
A = zeros(n);
b = zeros(n,1);
for i=1:n
    for j=1:n
        A(i,j) = 1 / (i + j - 1);
    end
end
for i=1:n
    sum = 0;
    for j=1:n
        sum = sum + A(i,j);
    end
    b(i) = sum;
end
[A, l] = Gauss(A);
x10 = Solve(A, l, b)

% Hilbert matrix system for n = 15
n = 15;
A = zeros(n);
b = zeros(n,1);
for i=1:n
    for j=1:n
        A(i,j) = 1 / (i + j - 1);
    end
end
for i=1:n
    sum = 0;
    for j=1:n
        sum = sum + A(i,j);
    end
    b(i) = sum;
end
[A, l] = Gauss(A);
x15 = Solve(A, l, b)
% A solution for electronic problem 1.1.7.

clc;

% Input vector 
input = [-9,11,0,14,-28,-21,12,2,-26]
n = length(input);              % Length of vector

% Matlab builtins for mean, variance and standard
% deviation for debugging
% mean(input)
% var(input)
% std(input)

% Calculating mean
sum = 0;
for i=1:n
    sum = sum + input(i);
end
avg = sum/n

% Calculating variance
varsum = 0;
for i=1:n
    varsum = varsum + (input(i) - avg).^2;
end
variance = varsum / (n-1)

% Calculating standard deviation
std_dev = sqrt(variance)
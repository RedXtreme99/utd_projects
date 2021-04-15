% Solution for electronic problem 5.4.3.

format short;
format compact;
clc;            % Formatting and clearing screen

% Gauss integral calculation including change of variable factor
gauss_integral(@f)/2

% Function y=sinx/x with change of variable x=(t+1)/2 to evaluate the
% integral from [0,1]
function y = f(x)
    y = sin(x./2+1/2) ./ (x./2+1/2);
end
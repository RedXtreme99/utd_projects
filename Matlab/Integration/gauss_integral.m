% Electronic problem 5.4.1.

% Function to calculate gauss integral approximation given a function by
% using formula 8 in the book to approximate integral f(x) from [-1,1].
function result = gauss_integral(f)
    result = 5/9*f(-sqrt(3/5)) + 8/9*f(0) + 5/9*f(sqrt(3/5));
end
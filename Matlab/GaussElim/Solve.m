% Function definition Solve.m
% Takes as input back-substitution ready matrix A, solution vector b, and 
% index vector l, and outputs the matrix ready for back substitution with 
% the index vector used to solve it.
function x = Solve(A, l, b)
    n = length(A);
    x = zeros(n,1);     % Solution vector x
    
    % Apply eliminations to update target vector b
    for k=1:n-1
        for i=k+1:n
            b(l(i)) = b(l(i)) - A(l(i),k)*b(l(k));
        end
    end
    
    % Generate solution vector x with back substitution based on index
    % vector l,
    x(n) = b(l(n)) / A(l(n),n);
    for i=n-1:-1:1
        sum = b(l(i));
        for j=i+1:n
            sum = sum - A(l(i),j)*x(j);
        end
        x(i) = sum / A(l(i),i);
    end
end
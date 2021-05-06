% Function definition Jacobi.m
% Takes as input matrix A, solution vector b, and initial solution vector x.
% The program outputs the calculated solution and the number of iterations 
% it took to reach it.
function [x_new, k] = Jacobi(A, b, x)
    n = length(b);
    % Variables for current and previous iterations, return value x_new
    x_new = x;
    x_prev = x;
    % Known true solution
    x_actual = [-1, 1, -1, 1];
    % Return iteration value k when answer found
    for k=1:100
        for i=1:n
            % Calculate sum using x_prev and non-diagonal entries
            sum = 0;
            for j=1:n
                if i == j
                    continue
                else
                    sum = sum + A(i,j)*x_prev(j);
                end
            end
            % Calculate x_new using Jacobi formula
            x_new(i) = (b(i) - sum) / A(i,i);
        end
        % Check for convergence to known true solution
        if round(x_new,4) == round(x_actual, 4)
            break
        end
        % Update x_prev
        x_prev = x_new;
    end
end
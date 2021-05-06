% Function definition SOR.m
% Takes as input matrix A, solution vector b, initial solution vector x, 
% and relaxation factor omega. The program outputs the calculated solution 
% and the number of iterations it took to reach it.
function [x_new, k] = SOR(A, b, x, omega)
    n = length(b);
    % Variables for current and previous iterations, return value x_new
    x_new = x;
    x_prev = x;
    % Known true solution
    x_actual = [-1, 1, -1, 1];
    % Return iteration value k when answer found
    for k=1:100
        for i=1:n
            % Calculate sum using x_new and non-diagonal entries
            sum = 0;
            for j=1:n
                if i == j
                    continue
                else
                    sum = sum + A(i,j)*x_new(j);
                end
            end
            % Calculate x_new using SOR formula
            x_new(i) = omega*(b(i) - sum)/A(i,i) + (1-omega)*x_prev(i);
        end
        % Check for convergence to known true solution
        if round(x_new,4) == round(x_actual, 4)
            break
        end
        % Update x_prev
        x_prev = x_new;
    end
end
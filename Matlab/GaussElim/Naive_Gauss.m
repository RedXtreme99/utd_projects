% Function definition Naive_Gauss
% Takes as input the matrix A and column vector b, and returns
% vector x that satisfies Ax=b
function x = Naive_Gauss(A, b)
    n = length(b);
    % Pivot on the diagonals to reduce to upper triangular form
    for k = 1:n-1
        if A(k,k) == 0
            continue;
        end
        for i = k+1:n
            xmult = A(i,k)/A(k,k);
            A(i,k) = xmult;
            for j = k+1:n
                A(i,j) = A(i,j) - xmult * A(k,j);
            end
            b(i) = b(i) - xmult * b(k);
        end
    end
    
    % Begin back substitution with the last row
    if A(n,n) == 0
        if b(n) ~= 0
            disp("Error: No solution");
            x = NaN(n);
            return;
        else
            x(n) = 0;
        end
    else
        x(n) = b(n) / A(n,n);
    end
    
    % Continue back substitution
    for i = n-1:-1:1
        if A(i,i) == 0
            if b(i) ~= 0
                disp("Error: No solution");
                x = NaN(n);
                return;
            else
                x(i) = 0;
                continue;
            end
        else
            sum = b(i);
            for j = i+1:n
                sum = sum - A(i,j) * x(j);
            end
            x(i) = sum / A(i,i);
        end
    end
end
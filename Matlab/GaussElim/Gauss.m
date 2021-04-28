% Function definition Gauss.m
% Takes as input matrix A and and outputs the matrix ready
% for back substitution with the index vector used to solve it.
function [A, l] = Gauss(A)
    n = length(A);
    % Index vector l
    l = zeros(n,1);
    % Scale vector s
    s = zeros(n,1);
    
    % Initialize index and scale vectors
    for i=1:n
        l(i) = i;
        smax = 0;
        for j=1:n
            smax = max(smax, A(i,j));
        end
        s(i) = smax;
    end
    
    % Apply gaussian elimination with scaled partial pivoting
    for k=1:n-1
        % Select row based on largest ratio
        rmax = 0;
        for i=k:n
            r = abs(A(l(i),k) / s(l(i)));
            if r > rmax
                rmax = r;
                j = i;
            end
        end
        % Swap elements in index vector
        l([j k]) = l([k j]);
        % Perform elimination on other remaining rows
        for i=k+1:n
            xmult = A(l(i),k) / A(l(k),k);
            A(l(i),k) = xmult;
            for j=k+1:n
                A(l(i),j) = A(l(i),j) - xmult*A(l(k),j);
            end
        end
    end
end
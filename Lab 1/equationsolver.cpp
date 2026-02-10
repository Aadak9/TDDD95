/*
Author: Andreas Nordström, andno773

Problem description: The program reads several test cases, each representing a system of linear
    equations A x = b. The value n tells how large the system is. After that,
    the next n lines contain the matrix A, and the line after that contains the
    vector b. When n = 0, there are no more test cases.

    For each system we need to decide whether it has:
        - a single solution,
        - infinitely many solutions (“multiple”), or
        - no solution (“inconsistent”).
    Since everything is done with floating-point numbers, comparisons need to
    allow a bit of tolerance.

Algorithm: The program applies Gaussian elimination with partial pivoting to reduce the
    matrix to an upper-triangular form.

        1. Forward elimination:
            - For each column, choose as pivot the row with the largest absolute
              value in that column.
            - Swap rows when needed.
            - Eliminate the entries below the pivot.

        2. Back substitution:
            - Solve the variables starting from the last row.
            - Rows that become all zeros are checked: a zero row with a nonzero
              right-hand side means the system is inconsistent, while a zero row
              with zero on the right-hand side indicates a free variable, which
              leads to multiple solutions.

Time complexity: For each of the n columns,
    the algorithm may touch roughly n rows, and for each row update almost n
    entries. That gives n × n × n operations, which is why Gaussian elimination
    is O(n³).

Usage: Call gaussSolver(A, b) with an n x n matrix A and vector b.
    The function returns a GaussResult:
        - status = UNIQUE, and values[] contains the solution;
        - status = MULTIPLE for infinitely many solutions;
        - status = INCONSISTENT if the system cannot be solved.
*/

#include <iostream>
#include <vector>
#include <cmath>

const double EPS = 1e-3;

enum SolutionType 
{
    UNIQUE, 
    MULTIPLE, 
    INCONSISTENT
};

struct GaussResult
{
    SolutionType type;
    std::vector<double> solution;
};

//Gauss-function that returns one of three solutiontypes
GaussResult gauss(std::vector<std::vector<double>> A, std::vector<double> b) 
{
    int n = A.size();

    for (int col = 0, row = 0; col < n && row < n; col++) 
    {
        int sel = row;

        //Find the row with the largest absolute pivot in this column
        for (int i = row; i < n; i++) 
        {
            if (fabs(A[i][col]) > fabs(A[sel][col])) 
            {
                sel = i;
            }
        }

        //If pivot is basically zero, skip this column
        if (fabs(A[sel][col]) < EPS) 
        {
            continue;
        }

        //Move best pivot row into the current row position
        std::swap(A[sel], A[row]);
        std::swap(b[sel], b[row]);

        //Eliminate values below the pivot
        for (int i = row + 1; i < n; i++) 
        {
            double factor = A[i][col] / A[row][col];

            //Update the row elements
            for (int j = col; j < n; j++) 
            {
                A[i][j] -= factor * A[row][j];
            }

            //Update the RHS
            b[i] -= factor * b[row];
        }

        row++;
    }

    std::vector<double> x(n, 0);

    for (int i = n - 1; i >= 0; i--) 
    {
        int pivot = -1;

        //Find first non-zero value in the row (pivot)
        for (int j = 0; j < n; j++) 
        {
            if (fabs(A[i][j]) > EPS) 
            {
                pivot = j;
                break;
            }
        }

        //If row is all zeros
        if (pivot == -1) 
        {
            //Zero row but RHS is non-zero > impossible system
            if (fabs(b[i]) > EPS) 
            {
                return {INCONSISTENT, {}};
            }
            continue;
        }

        //Compute the right-hand side minus known variables
        double sum = 0;
        for (int j = pivot + 1; j < n; j++) 
        {
            sum += A[i][j] * x[j];
        }

        x[pivot] = (b[i] - sum) / A[i][pivot];
    }

    for (int i = 0; i < n; i++) 
    {
        bool all_zero = true;

        //Check if entire row of A is zero
        for (int j = 0; j < n; j++) 
        {
            if (fabs(A[i][j]) > EPS) 
            {
                all_zero = false;
            }
        }

        //Zero row + zero RHS → free variable situation
        if (all_zero && fabs(b[i]) < EPS) 
        {
            return {MULTIPLE, {}};
        }
    }

    return {UNIQUE, x};
}


int main()
{
    int n;
    while (std::cin >> n && n != 0) 
    {        
        std::vector<std::vector<double>> A(n, std::vector<double>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) 
            {
                std::cin >> A[i][j];
            }
        }
        std::vector<double> b(n);
        for (int i = 0; i < n; i++) 
        {
            std::cin >> b[i];
        }
        GaussResult result = gauss(A, b);
        if (result.type == INCONSISTENT)
        {
            std::cout << "inconsistent" << '\n';
        }
        else if (result.type == MULTIPLE)
        {
            std::cout << "multiple" << '\n';
        }
        else 
        {
            for (double value : result.solution)
            {
                std::cout << value << " ";
            }
            std::cout << '\n';
        }
    }
    return 0;
}
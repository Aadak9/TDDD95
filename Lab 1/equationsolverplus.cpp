/*
Author: Andreas Nordström, andno773

Problem description: The program reads several test cases, each representing a system of linear
    equations A x = b. The value n tells how large the system is. After that,
    the next n lines contain the matrix A, and the line after that contains the
    vector b. When n = 0, there are no more test cases.

    For each system we need to decide whether it has:
        - a single solution,
        - multiple solutions to a variable
        - no solution (“inconsistent”).
    Since everything is done with floating-point numbers, comparisons need to
    allow a bit of tolerance.

Algorithm: RREF elimination:
     - For each column, pick the row with the largest pivot.
      - Swap rows if needed.
      - Eliminate all other entries in that column (both above and below) to isolate
        the variable in that column.

        Solution computation:
      - Pivot columns give the value of the corresponding variable.
      - Columns without a pivot are free variables and marked with '?'.

     Consistency check:
      - After computing the solution, verify that all rows satisfy the equations.
      - If any row fails (sum ≠ right-hand side), the system is inconsistent.


Time complexity: For each of the n columns,
    the algorithm may touch roughly n rows, and for each row update almost n
    entries. That gives n × n × n operations, which is why Gaussian elimination
    is O(n³).


Usage: Call gaussSolver(A, b) with an n × n matrix A and vector b.
The function returns a GaussResult:
    - status = UNIQUE, and solution[] contains the values for all variables; free variables are marked as '?'.
    - status = INCONSISTENT if the system cannot be solved.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>

const double EPS = 1e-9;

enum SolutionType
{
    UNIQUE,
    INCONSISTENT
};

struct GaussResult
{
    SolutionType type;
    std::vector<std::string> solution;
};

//Gaussian elimination function that
//returns solutiontype.
GaussResult gauss(std::vector<std::vector<double>> A)
{
    int n = A.size();
    int m = n;
    std::vector<int> where(m, -1);

    for (int col = 0, row = 0; col < m && row < n; col++)
    {
        //Select the row with the largest pivot in this column
        int sel = row;
        for (int i = row; i < n; i++)
        {
            if (std::abs(A[i][col]) > std::abs(A[sel][col]))
            {
                sel = i;
            }
        }

        //Skip column if pivot is effectively zero
        if (std::abs(A[sel][col]) < EPS)
        {
            continue;
        }

        for (int j = col; j <= m; j++)
        {
            std::swap(A[sel][j], A[row][j]);
        }

        where[col] = row;

        //Eliminate all other rows in this column, above and below
        for (int i = 0; i < n; i++)
        {
            if (i != row)
            {
                double factor = A[i][col] / A[row][col];
                for (int j = col; j <= m; j++)
                {
                    A[i][j] -= A[row][j] * factor;
                }
            }
        }

        row++;
    }

    //Back-substitution: compute solution for determined variables
    std::vector<double> ans(m, 0.0);

    for (int i = 0; i < m; i++)
    {
        if (where[i] != -1)
        {
            ans[i] = A[where[i]][m] / A[where[i]][i];
        }
    }

    // Check consistency
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < m; j++)
        {
            sum += ans[j] * A[i][j];
        }

        if (std::abs(sum - A[i][m]) > EPS)
        {
            return {INCONSISTENT, {}};
        }
    }

    std::vector<std::string> solution(m);
    for (int i = 0; i < m; i++)
    {
        bool determined = true;

        // Check if the variable depends on a free variable
        for (int j = 0; j < m; j++)
        {
            if (std::abs(A[i][j]) > EPS && where[j] == -1)
            {
                determined = false;
                break;
            }
        }

        if (!determined || where[i] == -1)
        {
            solution[i] = "?";
        }
        else
        {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << ans[i];
            solution[i] = ss.str();
        }
    }

    return {UNIQUE, solution};
}

int main()
{
    int n;
    while (std::cin >> n && n != 0)
    {
        std::vector<std::vector<double>> A(n, std::vector<double>(n + 1));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cin >> A[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            std::cin >> A[i][n];
        }

        GaussResult res = gauss(A);

        if (res.type == INCONSISTENT)
        {
            std::cout << "inconsistent\n";
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (i > 0)
                {
                    std::cout << " ";
                }
                std::cout << res.solution[i];
            }
            std::cout << "\n";
        }
    }
}
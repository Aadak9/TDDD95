#include <iostream>
#include <vector>
#include <string>

int literalToIndex(const std::string &lit)
{
    if (lit[0] == '~')
    {
        return std::stoi(lit.substr(2)) - 1;
    }
    else
    {
        return std::stoi(lit.substr(1)) - 1;
    }
}

bool clauseSatisfied(const std::vector<std::string> &clause, const std::vector<int> &assignment)
{
    for (size_t i = 0; i < clause.size(); i++)
    {
        std::string lit = clause[i];
        int idx = literalToIndex(lit);
        bool neg = lit[0] == '~';
        if ((assignment[idx] == 1 && !neg) || (assignment[idx] == 0 && neg))
        {
            return true;
        }
    }
    return false;
}

bool solveSAT(int var, int numVars, const std::vector<std::vector<std::string>> &clauses, std::vector<int> &assignment)
{
    if (var == numVars)
    {
        for (size_t i = 0; i < clauses.size(); i++)
        {
            if (!clauseSatisfied(clauses[i], assignment))
            {
                return false;
            }
        }
        return true;
    }

    assignment[var] = 0;
    if (solveSAT(var + 1, numVars, clauses, assignment))
    {
        return true;
    }

    assignment[var] = 1;
    if (solveSAT(var + 1, numVars, clauses, assignment))
    {
        return true;
    }

    return false;
}

std::vector<std::vector<std::string>> readClauses(int m)
{
    std::vector<std::vector<std::string>> clauses(m);
    for (int i = 0; i < m; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        size_t start = 0;
        for (size_t j = 0; j <= line.size(); j++)
        {
            if (j == line.size() || (line[j] == ' ' && line[j + 1] == 'v'))
            {
                clauses[i].push_back(line.substr(start, j - start));
                start = j + 3;
                j += 2;
            }
        }
    }
    return clauses;
}

int main()
{
    int T;
    std::cin >> T;
    std::cin.ignore();

    for (int t = 0; t < T; t++)
    {
        int n, m;
        std::cin >> n >> m;
        std::cin.ignore();

        std::vector<std::vector<std::string>> clauses = readClauses(m);
        std::vector<int> assignment(n, -1);

        if (solveSAT(0, n, clauses, assignment))
        {
            std::cout << "satisfiable\n";
        }
        else
        {
            std::cout << "unsatisfiable\n";
        }
    }

    return 0;
}



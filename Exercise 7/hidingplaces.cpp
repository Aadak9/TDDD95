#include <iostream>
#include <vector>
#include <string>
#include <climits>

const int SIZE = 8;

const int moveX[8] = {2, 2, -2, -2, 1, -1, 1, -1};
const int moveY[8] = {1, -1, 1, -1, 2, 2, -2, -2};

int steps[SIZE][SIZE];

bool validSquare(int r, int c)
{
    if (r >= 0 && r < SIZE && c >= 0 && c < SIZE)
    {
        return true;
    }
    return false;
}

void dfs(int r, int c, int count)
{
    if (count >= steps[r][c])
    {
        return;
    }

    steps[r][c] = count;

    for (int k = 0; k < 8; k++)
    {
        int nr = r + moveX[k];
        int nc = c + moveY[k];

        if (validSquare(nr, nc))
        {
            dfs(nr, nc, count + 1);
        }
    }
}

void getFarthestSquares(const std::string& startPos, int& maxSteps, std::vector<std::string>& farSquares
)
{
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            steps[r][c] = INT_MAX;
        }
    }

    int col = startPos[0] - 'a';
    int row = startPos[1] - '1';

    dfs(row, col, 0);

    maxSteps = 0;

    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (steps[r][c] > maxSteps)
            {
                maxSteps = steps[r][c];
            }
        }
    }

    farSquares.clear();

    for (int r = SIZE - 1; r >= 0; r--)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (steps[r][c] == maxSteps)
            {
                std::string sq;
                sq += char('a' + c);
                sq += char('1' + r);
                farSquares.push_back(sq);
            }
        }
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++)
    {
        std::string start;
        std::getline(std::cin, start);

        int answer;
        std::vector<std::string> result;

        getFarthestSquares(start, answer, result);

        std::cout << answer;

        for (std::size_t j = 0; j < result.size(); j++)
        {
            std::cout << " " << result[j];
        }

        std::cout << '\n';
    }

    return 0;
}

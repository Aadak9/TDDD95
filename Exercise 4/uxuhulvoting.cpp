#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string outcomeToString(int outcome) 
{
    std::string result;
    for (int i = 2; i >= 0; --i) 
    {
        if (outcome & (1 << i)) 
        {
            result += 'Y';
        } else {
            result += 'N';
        }
    }
    return result;
}

std::string solveVotingRound(int n, const std::vector<std::vector<int>>& prefs) 
{
    std::vector<std::vector<int>> dp(8, std::vector<int>(n + 1, -1));

    for (int state = 0; state < 8; ++state) 
    {
        dp[state][n] = state;
    }

    for (int player = n - 1; player >= 0; --player) 
    {
        for (int state = 0; state < 8; ++state) 
        {
            int best = -1;
            int bestPref = 1000000000;
            for (int stone = 0; stone < 3; ++stone) 
            {
                int nextState = state ^ (1 << stone);
                int outcome = dp[nextState][player + 1];
                int pref = prefs[player][outcome];
                if (pref < bestPref) 
                {
                    bestPref = pref;
                    best = outcome;
                }
            }
            dp[state][player] = best;
        }
    }

    int finalOutcome = dp[0][0];
    return outcomeToString(finalOutcome);
}

int main() 
{
    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int n;
        std::cin >> n;
        std::vector<std::vector<int>> prefs(n, std::vector<int>(8));
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < 8; ++j) 
            {
                std::cin >> prefs[i][j];
            }
        }

        std::string result = solveVotingRound(n, prefs);
        std::cout << result << std::endl;
    }

    return 0;
}

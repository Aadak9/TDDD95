#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

std::string DP(int n, std::vector<int> dist) 
{
    int sum = 0;
    for (int i = 0; i < n; i++) 
    {
        sum += dist[i];
    }

    if (sum % 2 == 1 || *std::max_element(dist.begin(), dist.end()) > sum / 2) 
    {
        return "IMPOSSIBLE";
    }

    int S = sum;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(S + 1, INT_MAX));
    dp[0][0] = 0;

    std::vector<std::vector<char>> parent(n + 1, std::vector<char>(S + 1, '?'));

    for (int i = 0; i < n; i++) 
    {
        int d = dist[i];

        for (int h = 0; h <= S; h++) 
        {
            if (dp[i][h] == INT_MAX) 
            {
                continue;
            }
            if (h + d <= S) 
            {
                int newPeak = dp[i][h];
                if (h + d > newPeak)
                {
                    newPeak = h + d;
                }

                if (newPeak < dp[i + 1][h + d]) 
                {
                    dp[i + 1][h + d] = newPeak;
                    parent[i + 1][h + d] = 'U';
                }
            }
            if (h >= d) 
            {
                int newPeak = dp[i][h];

                if (newPeak < dp[i + 1][h - d]) 
                {
                    dp[i + 1][h - d] = newPeak;
                    parent[i + 1][h - d] = 'D';
                }
            }
        }
    }

    if (dp[n][0] == INT_MAX) 
    {
        return "IMPOSSIBLE";
    }

    std::string sequence;
    int h = 0;

    for (int i = n; i > 0; i--) 
    {
        char c = parent[i][h];
        sequence.push_back(c);

        if (c == 'U') 
        {
            h -= dist[i - 1];
        } 
        else 
        {
            h += dist[i - 1];
        }
    }
    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() 
{
    int D;
    std::cin >> D;

    std::vector<std::string> results;

    for (int i = 0; i < D; i++) 
    {
        int n;
        std::cin >> n;

        std::vector<int> dist(n);
        for (int i = 0; i < n; i++) 
        {
            std::cin >> dist[i];
        }

        results.push_back(DP(n, dist));
    }

    for (size_t i = 0; i < results.size(); i++) 
    {
        std::cout << results[i] << "\n";
    }

    return 0;
}




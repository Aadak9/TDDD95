#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

int main() 
{
    int D;
    std::cin >> D;

    std::vector<std::string> results;

    while (D--) 
    {
        int n;
        std::cin >> n;

        std::vector<int> dist(n);
        int sum = 0;
        for (int i = 0; i < n; i++) 
        {
            std::cin >> dist[i];
            sum += dist[i];
        }
        if (sum % 2 == 1 || *std::max_element(dist.begin(), dist.end()) > sum / 2) 
        {
            results.push_back("IMPOSSIBLE");
            continue;
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
                    int newPeak = std::max(dp[i][h], h + d);
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
            results.push_back("IMPOSSIBLE");
            continue;
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
            } else 
            {
                h += dist[i - 1];
            }
        }
        std::reverse(sequence.begin(), sequence.end());
        results.push_back(sequence);
    }

    for (auto &x : results) 
    {
        std::cout << x << "\n";
    }

    return 0;
}



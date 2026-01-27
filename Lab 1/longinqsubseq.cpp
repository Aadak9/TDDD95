#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

//TODO Comments


std::pair<int, std::vector<int>> longestIncreasingSubsequence(const std::vector<int>& input)
{
    int n = input.size();
    if (n == 0) 
    {
        return {0, {}};
    }

    std::vector<int> tail;  
    std::vector<int> tailIndex;  
    std::vector<int> parent(n, -1);

    for (int i = 0; i < n; i++)
    {
        auto it = std::lower_bound(tail.begin(), tail.end(), input[i]);
        int pos = it - tail.begin();

        if (it == tail.end()) 
        {
            tail.push_back(input[i]);
            tailIndex.push_back(i);
        } 
        else 
        {
            tail[pos] = input[i];
            tailIndex[pos] = i;
        }

        if (pos > 0) 
        {
            parent[i] = tailIndex[pos - 1];
        }
    }
    int length = tail.size();
    std::vector<int> indices;

    int cur = tailIndex[length - 1];
    while (cur != -1) 
    {
        indices.push_back(cur); 
        cur = parent[cur];
    }

    std::reverse(indices.begin(), indices.end());

    return {length, indices};
}

int main()
{
    int N;

    while (std::cin >> N) 
    {
        std::vector<int> line(N);
        for (int i = 0; i < N; i++) 
        {
            std::cin >> line[i];
        }

        auto result = longestIncreasingSubsequence(line);

        std::cout << result.first << '\n';
        for (int idx : result.second) 
        {
            std::cout << idx << " ";
        }
        std::cout << '\n';
    }
    return 0;
}


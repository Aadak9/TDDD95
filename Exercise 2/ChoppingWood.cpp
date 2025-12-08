#include <iostream>
#include <vector>
#include <queue>

std::string choopWood(const std::vector<int>& input)
{
    if (input.empty())
    {
        return "Error";
    }

    int n = input[0];

    std::vector<int> v;
    v.reserve(input.size() - 1);
    for (size_t i = 1; i < input.size(); i++)
    {
        v.push_back(input[i]);
    }

    int m = v.size();

    std::vector<int> count(n + 1, 0);
    for (size_t i = 0; i < v.size(); i++)
    {
        int val = v[i];
        count[val]++;
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

    for (int node = 1; node <= n; node++)
    {
        if (count[node] == 0)
        {
            heap.push(node);
        }
    }
    std::vector<int> u;
    u.reserve(m);

    for (int i = 0; i < m; i++)
    {
        if (heap.empty())
        {
            return "Error";
        }

        int leaf = heap.top();
        heap.pop();

        if (leaf == v[i])
        {
            return "Error";
        }

        u.push_back(leaf);

        count[v[i]]--;
        if (count[v[i]] == 0)
        {
            heap.push(v[i]);
        }
    }
    std::string output;
    for (size_t i = 0; i < u.size(); i++)
    {
        output += std::to_string(u[i]);
        output += '\n';
    }
    return output;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> input;
    int x;

    while (std::cin >> x)
    {
        input.push_back(x);
    }
    std::string result = choopWood(input);
    std::cout << result;

    return 0;
}


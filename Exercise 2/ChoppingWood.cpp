#include <iostream>
#include <vector>
#include <queue>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> input;
    int x;

    while (std::cin >> x)
    {
        input.push_back(x);
    }

    if (input.empty())
    {
        std::cout << "Error\n";
        return 0;
    }

    int n = input[0];
    std::vector<int> v;
    v.reserve(input.size() - 1);

    for (size_t i = 1; i < input.size(); i++)
    {
        v.push_back(input[i]);
    }

    int m = v.size();
    std::vector<int> count(n+1, 0);
    for (int val : v)
    {
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
            std::cout << "Error\n";
            return 0;
        }

        int leaf = heap.top();
        heap.pop();
        if (leaf == v[i])
        {
            std::cout << "Error\n";
            return 0;
        }

        u.push_back(leaf);
        count[v[i]]--;
        if (count[v[i]] == 0)
        {
            heap.push(v[i]);
        }
    }

    for (int x : u)
        std::cout << x << "\n";

    return 0;
}

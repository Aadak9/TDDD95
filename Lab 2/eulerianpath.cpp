/*
Author: Andreas Nordström, andno773

Problem description: 

Algorithm: 


Time complexity: 


Usage: 
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

std::vector<int> find_euler_path(int n, int m, const std::vector<std::pair<int, int>> &edges)
{
    std::vector<std::vector<std::pair<int, int>>> adj;
    adj.assign(n, std::vector<std::pair<int, int>>());

    std::vector<int> indeg(n, 0);
    std::vector<int> outdeg(n, 0);

    for (int i = 0; i < m; i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back({v, i});
        outdeg[u]++;
        indeg[v]++;
    }

    int start = -1;
    int plus1 = 0;
    int minus1 = 0;

    for (int i = 0; i < n; i++)
    {
        if (outdeg[i] - indeg[i] == 1)
        {
            plus1++;
            start = i;
        }
        else
        {
            if (indeg[i] - outdeg[i] == 1)
            {
                minus1++;
            }
            else
            {
                if (indeg[i] != outdeg[i])
                {
                    return {};
                }
            }
        }
    }

    if (!((plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0)))
    {
        return {};
    }

    if (start == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (outdeg[i] > 0)
            {
                start = i;
                break;
            }
        }
    }

    if (start == -1)
    {
        return {};
    }

    std::vector<bool> used(m, false);
    std::vector<int> idx(n, 0);
    std::vector<int> path;
    std::stack<int> st;

    st.push(start);

    while (!st.empty())
    {
        int u = st.top();

        while (idx[u] < (int)adj[u].size() && used[adj[u][idx[u]].second])
        {
            idx[u]++;
        }

        if (idx[u] == (int)adj[u].size())
        {
            path.push_back(u);
            st.pop();
        }
        else
        {
            int v = adj[u][idx[u]].first;
            int id = adj[u][idx[u]].second;

            used[id] = true;
            st.push(v);
        }
    }

    if ((int)path.size() != m + 1)
    {
        return {};
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (true)
    {
        int n;
        int m;

        std::cin >> n >> m;

        if (!std::cin || (n == 0 && m == 0))
        {
            break;
        }

        std::vector<std::pair<int, int>> edges;

        for (int i = 0; i < m; i++)
        {
            int u;
            int v;

            std::cin >> u >> v;
            edges.push_back({u, v});
        }

        std::vector<int> path = find_euler_path(n, m, edges);

        if (path.empty())
        {
            std::cout << "Impossible\n";
        }
        else
        {
            for (int i = 0; i < (int)path.size(); i++)
            {
                std::cout << path[i];

                if (i + 1 < (int)path.size())
                {
                    std::cout << " ";
                }
            }

            std::cout << "\n";
        }
    }

    return 0;
}
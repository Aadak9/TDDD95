/*
Author: Andreas Nordström, andno773

Problem description: 

Algorithm: 


Time complexity: 


Usage: 
*/

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

struct Edge
{
    int from;
    int to;
    long long w;
};

struct BellmanFordResult
{
    std::vector<long long> dist;
    std::vector<int> parent;
    std::vector<bool> neg_inf;
};

BellmanFordResult bellman_ford(int n, int start, const std::vector<Edge> &edges)
{
    const long long INF = std::numeric_limits<long long>::max();

    std::vector<long long> dist(n, INF);
    std::vector<int> parent(n, -1);
    std::vector<bool> neg_inf(n, false);

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (const Edge &e : edges)
        {
            if (dist[e.from] == INF)
            {
                continue;
            }

            if (dist[e.from] + e.w < dist[e.to])
            {
                dist[e.to] = dist[e.from] + e.w;
                parent[e.to] = e.from;
            }
        }
    }

    std::queue<int> q;

    for (const Edge &e : edges)
    {
        if (dist[e.from] == INF)
        {
            continue;
        }

        if (dist[e.from] + e.w < dist[e.to])
        {
            neg_inf[e.to] = true;
            q.push(e.to);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const Edge &e : edges)
        {
            if (e.from == u)
            {
                if (!neg_inf[e.to])
                {
                    neg_inf[e.to] = true;
                    q.push(e.to);
                }
            }
        }
    }

    BellmanFordResult result;
    result.dist = dist;
    result.parent = parent;
    result.neg_inf = neg_inf;

    return result;
}

std::vector<int> build_path(int target, const std::vector<int> &parent)
{
    std::vector<int> path;

    int v = target;

    while (v != -1)
    {
        path.push_back(v);
        v = parent[v];
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
        int q;
        int start;

        std::cin >> n >> m >> q >> start;

        if (!std::cin || (n == 0 && m == 0 && q == 0 && start == 0))
        {
            break;
        }

        std::vector<Edge> edges;

        for (int i = 0; i < m; i++)
        {
            int u;
            int v;
            long long w;

            std::cin >> u >> v >> w;

            Edge e;
            e.from = u;
            e.to = v;
            e.w = w;

            edges.push_back(e);
        }

        BellmanFordResult result = bellman_ford(n, start, edges);

        for (int i = 0; i < q; i++)
        {
            int target;
            std::cin >> target;

            if (result.neg_inf[target])
            {
                std::cout << "-Infinity\n";
            }
            else
            {
                if (result.dist[target] == std::numeric_limits<long long>::max())
                {
                    std::cout << "Impossible\n";
                }
                else
                {
                    std::cout << result.dist[target] << "\n";

                    /*
                    std::vector<int> path = build_path(target, result.parent);

                    for (size_t j = 0; j < path.size(); j++)
                    {
                        std::cout << path[j];

                        if (j + 1 < path.size())
                        {
                            std::cout << " ";
                        }
                    }

                    std::cout << "\n";
                    */
                }
            }
        }

        std::cout << "\n";
    }

    return 0;
}
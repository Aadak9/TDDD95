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

struct FloydWarshallResult
{
    std::vector<std::vector<long long>> dist;
    std::vector<std::vector<bool>> neg_inf;
};

FloydWarshallResult floyd_warshall(int n, const std::vector<std::vector<long long>> &graph)
{
    const long long INF = std::numeric_limits<long long>::max();

    std::vector<std::vector<long long>> dist = graph;
    std::vector<std::vector<bool>> neg_inf(n, std::vector<bool>(n, false));

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (dist[i][k] == INF)
            {
                continue;
            }

            for (int j = 0; j < n; j++)
            {
                if (dist[k][j] == INF)
                {
                    continue;
                }

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        if (dist[k][k] < 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (dist[i][k] == INF)
                {
                    continue;
                }

                for (int j = 0; j < n; j++)
                {
                    if (dist[k][j] == INF)
                    {
                        continue;
                    }

                    neg_inf[i][j] = true;
                }
            }
        }
    }

    FloydWarshallResult result;
    result.dist = dist;
    result.neg_inf = neg_inf;

    return result;
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

        std::cin >> n >> m >> q;

        if (!std::cin || (n == 0 && m == 0 && q == 0))
        {
            break;
        }

        const long long INF = std::numeric_limits<long long>::max();

        std::vector<std::vector<long long>> graph;

        graph.assign(n, std::vector<long long>(n, INF));

        for (int i = 0; i < n; i++)
        {
            graph[i][i] = 0;
        }

        for (int i = 0; i < m; i++)
        {
            int u;
            int v;
            long long w;

            std::cin >> u >> v >> w;

            if (w < graph[u][v])
            {
                graph[u][v] = w;
            }
        }

        FloydWarshallResult result = floyd_warshall(n, graph);

        for (int i = 0; i < q; i++)
        {
            int u;
            int v;

            std::cin >> u >> v;

            if (result.neg_inf[u][v])
            {
                std::cout << "-Infinity\n";
            }
            else
            {
                if (result.dist[u][v] == INF)
                {
                    std::cout << "Impossible\n";
                }
                else
                {
                    std::cout << result.dist[u][v] << "\n";
                }
            }
        }

        std::cout << "\n";
    }

    return 0;
}
/*
Author: Andreas Nordström, andno773

Problem description: Given a directed weighted graph, answer shortest path queries between
any pair of nodes.
- Output the shortest distance if a path exists
- Output "Impossible" if there is no path
- Output "-Infinity" if the path is affected by a negative cycle

Algorithm: Floyd-Warshall is used to compute shortest paths between all pairs of nodes.

The idea is to gradually allow more intermediate nodes when trying to
improve paths. For each node k, it checks whether going through k gives
a shorter path from i to j.

After computing all distances, nodes that are part of a negative cycle
are identified by checking if dist[k][k] < 0. If such a node k exists,
then any path that can go through k is affected. Those pairs are marked
separately and treated as having distance −inf.


Time complexity: The algorithm runs in O(n^3), since it uses three nested loops over
all nodes. Handling negative cycles is also O(n^3), but does not change
the overall complexity.


Usage: Input consists of multiple test cases.

For each test case:
- n = number of nodes
- m = number of edges
- q = number of queries

Then m lines: u v w (edge from u to v with weight w)
Then q queries: u v

Ends when n = m = q = 0
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
    
    //neg_inf[i][j] = true if shortest path from i to j is affected by a negative cycle
    std::vector<std::vector<bool>> neg_inf(n, std::vector<bool>(n, false));

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            //Skip if i cannot reach k
            if (dist[i][k] == INF)
            {
                continue;
            }

            for (int j = 0; j < n; j++)
            {
                //Skip if k cannot reach j
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

    //Detect negative cycles and mark all affected pairs
    for (int k = 0; k < n; k++)
    {
        //A negative value on the diagonal means a negative cycle involving k
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

                    //Any path that can go through k is affected by the negative cycle
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
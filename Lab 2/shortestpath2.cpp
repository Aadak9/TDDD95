/*
Author: Andreas Nordström, andno773

Problem description: 

Algorithm: 


Time complexity: 


Usage: 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

struct Edge
{
    int to;
    long long t0;
    long long p;
    long long w;
};

struct DijkstraResult
{
    std::vector<long long> dist;
    std::vector<int> parent;
};

DijkstraResult dijkstra(int n, int start, const std::vector<std::vector<Edge>> &graph)
{
    const long long INF = std::numeric_limits<long long>::max();

    std::vector<long long> dist(n, INF);
    std::vector<int> parent(n, -1);

    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

    dist[start] = start;   // start at node s at time s
    pq.push(std::make_pair(start, start));

    while (!pq.empty())
    {
        long long currentTime = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currentTime > dist[node])
        {
            continue;
        }

        for (std::size_t i = 0; i < graph[node].size(); i++)
        {
            const Edge &e = graph[node][i];

            long long nextDeparture = -1;

            if (currentTime <= e.t0)
            {
                // We can catch the first available time
                nextDeparture = e.t0;
            }
            else
            {
                if (e.p == 0)
                {
                    // Only usable exactly at t0, and we are too late
                    continue;
                }

                // Wait until t0 + k*p >= currentTime
                long long k = (currentTime - e.t0 + e.p - 1) / e.p;
                nextDeparture = e.t0 + k * e.p;
            }

            long long arrival = nextDeparture + e.w;

            if (arrival < dist[e.to])
            {
                dist[e.to] = arrival;
                parent[e.to] = node;
                pq.push(std::make_pair(arrival, e.to));
            }
        }
    }

    DijkstraResult result;
    result.dist = dist;
    result.parent = parent;
    return result;
}

std::vector<int> build_path(int target, const std::vector<int> &parent)
{
    std::vector<int> path;

    int node = target;
    while (node != -1)
    {
        path.push_back(node);
        node = parent[node];
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
        int n, m, q, start;
        std::cin >> n >> m >> q >> start;

        if (!std::cin || (n == 0 && m == 0 && q == 0 && start == 0))
        {
            break;
        }

        std::vector<std::vector<Edge>> graph;
        graph.resize(n);

        for (int i = 0; i < m; i++)
        {
            int u, v;
            long long t0, p, w;
            std::cin >> u >> v >> t0 >> p >> w;

            Edge e;
            e.to = v;
            e.t0 = t0;
            e.p = p;
            e.w = w;

            graph[u].push_back(e);
        }

        DijkstraResult result = dijkstra(n, start, graph);

        for (int i = 0; i < q; i++)
        {
            int target;
            std::cin >> target;

            if (result.dist[target] == std::numeric_limits<long long>::max())
            {
                std::cout << "Impossible\n";
            }
            else
            {
                std::cout << result.dist[target] << "\n";

                std::vector<int> path = build_path(target, result.parent);

                for (std::size_t j = 0; j < path.size(); j++)
                {
                    std::cout << path[j];
                    if (j + 1 < path.size())
                    {
                        std::cout << " ";
                    }
                }
                std::cout << "\n";
            }
        }

        std::cout << "\n";
    }

    return 0;
}
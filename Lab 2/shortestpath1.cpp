/*
Author: Andreas Nordström, andno773

Problem description: Given a directed weighted graph, answer multiple shortest path queries
from a given start node to different target nodes. If a node is not
reachable, output "Impossible".

Algorithm: Dijkstra's algorithm with a priority queue (min-heap) to compute
the shortest distance from the start node to all other nodes in the graph.
The graph is represented as an adjacency list.

We also store parent pointers to reconstruct paths if needed.


Time complexity: - Dijkstra: O((n + m) log n)
  where n = number of nodes, m = number of edges
- Each query: O(1) after preprocessing


Usage: Input consists of multiple test cases.
For each test case:
- n = number of nodes
- m = number of edges
- q = number of queries
- start = starting node

Then m lines of edges: u v w (edge from u to v with weight w)
Then q lines of queries: target node

Ends when n = m = q = start = 0
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

struct DijkstraResult
{
    std::vector<long long> dist;
    std::vector<int> parent;
};

DijkstraResult dijkstra(int n, int start, const std::vector<std::vector<std::pair<int, int>>> &graph)
{
    const long long INF = std::numeric_limits<long long>::max();

    std::vector<long long> dist(n, INF);
    std::vector<int> parent(n, -1);

    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

    dist[start] = 0;
    pq.push(std::make_pair(0, start));

    while (!pq.empty())
    {
        long long currentDistance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        //Skip outdated entries
        if (currentDistance > dist[node])
        {
            continue;
        }

        for (std::size_t i = 0; i < graph[node].size(); i++)
        {
            int next = graph[node][i].first;
            int weight = graph[node][i].second;

            if (dist[node] + weight < dist[next])
            {
                dist[next] = dist[node] + weight;
                parent[next] = node;
                pq.push(std::make_pair(dist[next], next));
            }
        }
    }

    DijkstraResult result;
    result.dist = dist;
    result.parent = parent;
    return result;
}

//Reconstruct path from start to target using parent array
std::vector<int> build_path(int target, const std::vector<int> &parent)
{
    std::vector<int> path;

    int node = target;
    while (node != -1)
    {
        path.push_back(node);
        node = parent[node]; //move backwards
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

        std::vector<std::vector<std::pair<int, int>>> graph(n);

        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;
            graph[u].push_back(std::make_pair(v, w));
        }

        DijkstraResult result = dijkstra(n, start, graph);

        for (int i = 0; i < q; i++)
        {
            int target;
            std::cin >> target;

            if (result.dist[target] == std::numeric_limits<long long>::max())
            {
                std::cout << "Impossible" << '\n';
            }
            else
            {
                std::cout << result.dist[target] << '\n';
                /*
                std::vector<int> path = build_path(target, result.parent);

                for (std::size_t j = 0; j < path.size(); j++)
                {
                    std::cout << path[j];
                    if (j + 1 < path.size())
                    {
                        std::cout << " ";
                    }
                }
                std::cout << '\n';
                */
            }
        }

        std::cout << '\n';
    }

    return 0;
}
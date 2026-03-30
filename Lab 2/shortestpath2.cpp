/*
Author: Andreas Nordström, andno773

Problem description: We are given a directed graph where each edge represents a time-dependent
connection. Each edge (u → v) has:
- t0: the first time the edge can be used
- p: the period (how often the edge repeats)
- w: the travel time

From a given start node, we must answer multiple queries asking for the
earliest arrival time to different target nodes. If a node is unreachable,
output "Impossible".

Algorithm: A modified version of Dijkstra’s algorithm is used where the “distance”
represents time instead of cost.

The key difference is that edges are time-dependent. For each node,
when processing it at time t, the earliest possible departure time for
each outgoing edge must be determined.

- If t ≤ t0, the edge can be taken at time t0.
- If t > t0:
  - If p = 0, the edge is no longer usable.
  - Otherwise, wait until the smallest time of the form t0 + k*p that is ≥ t.

After computing the departure time, the travel time w is added to get
the arrival time at the next node. If this improves the known best time,
the value is updated and pushed into the priority queue.

The process continues until all reachable nodes have their shortest
arrival times determined.


Time complexity: The algorithm runs in O((n + m) log n), just like standard Dijkstra.
Each edge relaxation only does a few constant-time calculations, so it
doesn’t change the overall complexity. Queries are answered in constant time.


Usage: Input consists of multiple test cases.
For each test case:
- n = number of nodes
- m = number of edges
- q = number of queries
- start = starting node

Then m lines:
u v t0 p w

Then q queries: target node

Ends when n = m = q = start = 0
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

    dist[start] = 0;   
    pq.push({0, start});

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
                //We can catch the first available time
                nextDeparture = e.t0;
            }
            else
            {
                if (e.p == 0)
                {
                    //Only usable exactly at t0, and we are too late
                    continue;
                }

                //Wait until t0 + k*p >= currentTime
                long long k = (currentTime - e.t0 + e.p - 1) / e.p;
                nextDeparture = e.t0 + k * e.p;
            }

             //Arrival time after taking the edge
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
                std::cout << "\n";
                */
            }
                
        }

        std::cout << "\n";
    }

    return 0;
}
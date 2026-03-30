/*
Author: Andreas Nordström, andno773

Problem description: Bellman-Ford is used to find shortest paths from the start node.
All edges are relaxed repeatedly (n−1 times), which is enough to
propagate the correct shortest distances as long as there are no
negative cycles involved.

After that, one more pass over the edges is done. If a distance can
still be improved, it means there is a negative cycle affecting that node.

Those nodes are then put into a queue, and a simple traversal is used
to mark every node that can be reached from them. All such nodes are
treated as having distance −inf.

Algorithm: Bellman-Ford is used to compute shortest paths. First, all edges are
relaxed n−1 times to find shortest distances.

After that, edges are checked once more to detect nodes that can still
be improved. These nodes are part of, or reachable from, a negative cycle.

A BFS/propagation step is then used to mark all nodes reachable from
those cycles as having distance −inf.


Time complexity: The relaxation step runs in O(n * m). The extra pass for detecting
negative cycles and the BFS propagation together take O(m + n).
Overall complexity is O(n * m).


Usage: Input consists of multiple test cases.

For each test case:
- n = number of nodes
- m = number of edges
- q = number of queries
- start = starting node

Then m lines: u v w (edge from u to v with weight w)
Then q queries: target node

Ends when n = m = q = start = 0
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
    std::vector<bool> neg_inf; //true if node is affected by negative cycle
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
                continue; //unreachable node
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

        //Detect nodes that can still be relaxed → part of negative cycle
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
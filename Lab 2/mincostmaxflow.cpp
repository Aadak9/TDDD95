/*
Author: Andreas Nordström, andno773

Problem description:
Given a directed graph where each edge has a capacity and a cost, the goal is
to send as much flow as possible from the source to the sink, while keeping
the total cost of that flow as small as possible.

Algorithm:
The solution combines maximum flow with cost minimization.

At each step, the algorithm finds the cheapest path from the source to the
sink in the residual graph. This is typically done using the Bellman-Ford
algorithm or a similar shortest path method that can handle negative edges.

Once a shortest path is found, as much flow as possible is pushed along that
path (limited by the remaining capacity of the edges on the path).

The residual graph is then updated, and the process repeats until no more
augmenting paths can be found.

The result is a flow with maximum value, and among all such flows, the one
with the minimum total cost.

Time complexity:
Using Bellman-Ford to find shortest paths, the complexity is
O(F * n * m), where F is the amount of flow sent, n is the number of nodes,
and m is the number of edges.

Usage:
Input:
- n = number of nodes
- m = number of edges
- s = source
- t = sink

Then m lines follow:
u v cap cost (edge from u to v with given capacity and cost)

Output:
- First number: value of the maximum flow
- Second number: total cost of that flow

The full flow itself can be reconstructed from the residual graph.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge
{
    int to;
    int cap;
    int cost;
    int flow;
    int rev;
};

std::vector<std::vector<Edge>> g;

//Add edge with reverse edge
void addEdge(int u, int v, int cap, int cost)
{
    Edge a = {v, cap, cost, 0, (int)g[v].size()};
    Edge b = {u, 0, -cost, 0, (int)g[u].size()};

    g[u].push_back(a);
    g[v].push_back(b);
}

//Shortest path (Bellman-Ford)
bool spfa(int n, int s, int t, std::vector<int> &dist, std::vector<int> &par, std::vector<int> &parEdge)
{
    dist.assign(n, std::numeric_limits<int>::max());
    std::vector<bool> inQueue(n, false);
    std::queue<int> q;

    dist[s] = 0;
    q.push(s);
    inQueue[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int i = 0; i < (int)g[u].size(); i++)
        {
            Edge &e = g[u][i];

            if (e.cap - e.flow > 0 && dist[u] + e.cost < dist[e.to])
            {
                dist[e.to] = dist[u] + e.cost;
                par[e.to] = u;
                parEdge[e.to] = i;

                if (!inQueue[e.to])
                {
                    q.push(e.to);
                    inQueue[e.to] = true;
                }
            }
        }
    }

    return dist[t] != std::numeric_limits<int>::max();
}

//Minimum Cost Maximum Flow
std::pair<int, int> min_cost_max_flow(int n, int s, int t)
{
    int flow = 0;
    int cost = 0;

    std::vector<int> dist(n), par(n), parEdge(n);

    //Continue while there is a path to the sink
    while (spfa(n, s, t, dist, par, parEdge))
    {
        int add = std::numeric_limits<int>::max();

        //Find bottleneck capacity
        for (int v = t; v != s; v = par[v])
        {
            int u = par[v];
            Edge &e = g[u][parEdge[v]];
            add = std::min(add, e.cap - e.flow);
        }

        //Apply flow and update cost
        for (int v = t; v != s; v = par[v])
        {
            int u = par[v];
            Edge &e = g[u][parEdge[v]];

            e.flow += add;
            g[v][e.rev].flow -= add;

            cost += add * e.cost;
        }

        flow += add;
    }

    return {flow, cost};
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    g.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, cap, cost;
        std::cin >> u >> v >> cap >> cost;
        addEdge(u, v, cap, cost);
    }

    auto result = min_cost_max_flow(n, s, t);

    std::cout << result.first << " " << result.second << "\n";

    return 0;
}
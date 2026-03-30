/*
Author: Andreas Nordström, andno773

Problem description:
Given a directed weighted graph with a source and a sink, the task is to
find a subset of vertices S such that:
- the source is in S
- the sink is not in S
- the total weight of edges going from S to the rest of the graph is minimized

After computing the maximum flow, the minimum cut can be obtained from the
residual graph by finding all vertices reachable from the source using only
edges with remaining capacity.

Algorithm:
The Edmonds–Karp algorithm is used to compute the maximum flow. It works by
repeatedly finding the shortest augmenting path (in terms of number of edges)
using BFS and then pushing as much flow as possible along that path.

Once no more augmenting paths can be found, the residual graph is explored
using BFS starting from the source. All vertices that can still be reached
form the set S of the minimum cut.

Time complexity:
dmonds–Karp runs in O(n * m^2), where n is the number of nodes and m is
the number of edges.

The final BFS to extract the cut runs in O(n + m).

Usage:
Input:
- n = number of nodes
- m = number of edges
- s = source node
- t = sink node

Then m lines follow:
u v w (directed edge from u to v with capacity w)

Output:
- First line: size of the set S
- Then the vertices in S, one per line

Any valid minimum cut is accepted.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Edge structure for flow graph
struct Edge
{
    int to;
    int cap;
    int flow;
    int rev;
};

std::vector<std::vector<Edge>> g;

// Add edge with reverse edge for residual graph
void addEdge(int u, int v, int c)
{
    Edge a = {v, c, 0, (int)g[v].size()};
    Edge b = {u, 0, 0, (int)g[u].size()};

    g[u].push_back(a);
    g[v].push_back(b);
}

// BFS to find augmenting path
bool bfs(int s, int t, std::vector<int> &par, std::vector<int> &parEdge)
{
    std::vector<bool> vis(g.size(), false);
    std::queue<int> q;

    q.push(s);
    vis[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)g[u].size(); i++)
        {
            Edge &e = g[u][i];

            if (!vis[e.to] && e.cap - e.flow > 0)
            {
                vis[e.to] = true;
                par[e.to] = u;
                parEdge[e.to] = i;

                if (e.to == t)
                {
                    return true;
                }

                q.push(e.to);
            }
        }
    }

    return false;
}

// Compute maximum flow (Edmonds–Karp)
int maxflow(int n, int s, int t)
{
    int flow = 0;

    std::vector<int> par(n);
    std::vector<int> parEdge(n);

    while (bfs(s, t, par, parEdge))
    {
        int add = 1000000000;

        for (int v = t; v != s; v = par[v])
        {
            int u = par[v];
            Edge &e = g[u][parEdge[v]];

            add = std::min(add, e.cap - e.flow);
        }

        for (int v = t; v != s; v = par[v])
        {
            int u = par[v];
            Edge &e = g[u][parEdge[v]];

            e.flow += add;
            g[v][e.rev].flow -= add;
        }

        flow += add;
    }

    return flow;
}

// Find vertices reachable from source in residual graph
std::vector<int> min_cut(int n, int s)
{
    std::vector<bool> vis(n, false);
    std::queue<int> q;

    q.push(s);
    vis[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const Edge &e : g[u])
        {
            // Only follow edges with remaining capacity
            if (!vis[e.to] && e.cap - e.flow > 0)
            {
                vis[e.to] = true;
                q.push(e.to);
            }
        }
    }

    std::vector<int> result;

    // All reachable nodes form the cut set
    for (int i = 0; i < n; i++)
    {
        if (vis[i])
        {
            result.push_back(i);
        }
    }

    return result;
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
        int u, v, c;
        std::cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    maxflow(n, s, t);

    std::vector<int> cut = min_cut(n, s);

    std::cout << cut.size() << "\n";

    for (int v : cut)
    {
        std::cout << v << "\n";
    }

    return 0;
}
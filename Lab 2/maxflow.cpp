/*
Author: Andreas Nordström, andno773

Problem description:
Given a directed graph with capacities on edges, compute the maximum flow
from a source node to a sink node.

After computing the max flow, also output all edges that carry positive flow.

Algorithm:
Edmonds–Karp is used, which is a specific implementation of the Ford–Fulkerson
method that always chooses the shortest augmenting path (in terms of number
of edges).

A BFS is used to find an augmenting path from the source to the sink in the
residual graph. Once a path is found, the smallest remaining capacity along
that path is determined and the flow is pushed through it.

The residual graph is then updated, and the process repeats until no more
augmenting paths can be found.


Time complexity: Each BFS takes O(m), and in the worst case, there can be up to O(n * m)
augmentations. This gives an overall complexity of O(n * m^2).


Usage: Input:
- n = number of nodes
- m = number of edges
- s = source node
- t = sink node

Then m lines follow:
u v c (directed edge from u to v with capacity c)

Output:
- First line: n, total max flow, and number of edges with positive flow
- Then each edge with positive flow: u v flow
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

struct Edge
{
    int to;
    int cap;
    int flow;
    int rev;
};

std::vector<std::vector<Edge>> g;

//Adds a forward edge and a corresponding backward (residual) edge
void addEdge(int u, int v, int c)
{
    Edge a;
    a.to = v;
    a.cap = c;
    a.flow = 0;
    a.rev = g[v].size();

    Edge b;
    b.to = u;
    b.cap = 0;
    b.flow = 0;
    b.rev = g[u].size();

    g[u].push_back(a);
    g[v].push_back(b);
}

//BFS to find an augmenting path and store parents
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

            //Only follow edges with remaining capacity
            if (!vis[e.to] && e.cap - e.flow > 0)
            {
                vis[e.to] = true;
                par[e.to] = u;
                parEdge[e.to] = i;

                //Stop early if sink is reached
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

int maxflow(int n, int s, int t)
{
    int flow = 0;

    std::vector<int> par(n);
    std::vector<int> parEdge(n);

    while (bfs(s, t, par, parEdge))
    {
        int add = 1000000000;

        //Find bottleneck
        for (int v = t; v != s; v = par[v])
        {
            int u = par[v];
            Edge &e = g[u][parEdge[v]];

            if (e.cap - e.flow < add)
            {
                add = e.cap - e.flow;
            }
        }

        //Apply the flow and update residual graph
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

int main()
{
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    g.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        std::cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    int f = maxflow(n, s, t);

    std::vector<std::tuple<int,int,int>> ans;

    for (int u = 0; u < n; u++)
    {
        for (int i = 0; i < (int)g[u].size(); i++)
        {
            Edge &e = g[u][i];

            if (e.flow > 0)
            {
                ans.push_back(std::make_tuple(u, e.to, e.flow));
            }
        }
    }

    std::cout << n << " " << f << " " << ans.size() << "\n";

    for (int i = 0; i < (int)ans.size(); i++)
    {
        std::cout << std::get<0>(ans[i]) << " "
                  << std::get<1>(ans[i]) << " "
                  << std::get<2>(ans[i]) << "\n";
    }

    return 0;
}
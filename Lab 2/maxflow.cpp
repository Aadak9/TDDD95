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
#include <tuple>

struct Edge
{
    int to;
    int cap;
    int flow;
    int rev;
};

std::vector<std::vector<Edge>> g;

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

            if (e.cap - e.flow < add)
            {
                add = e.cap - e.flow;
            }
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
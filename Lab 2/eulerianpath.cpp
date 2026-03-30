/*
Author: Andreas Nordström, andno773

Problem description: Given a directed graph, determine whether an Eulerian path exists and,
if it does, output one such path.

An Eulerian path is a path that uses every edge exactly once.

Algorithm: First, the graph is checked to see if an Eulerian path is possible.
For a directed graph, this depends on the in-degree and out-degree of each node.

- At most one node can have out-degree = in-degree + 1 (start node).
- At most one node can have in-degree = out-degree + 1 (end node).
- All other nodes must have equal in-degree and out-degree.

If these conditions are not met, no Eulerian path exists.

If a valid start node is found, Hierholzer’s algorithm is used to construct
the path. The algorithm walks through unused edges, using a stack to keep
track of the current path. When no more unused edges are available from a
node, it is added to the final path.

After all edges are used, the resulting path is reversed to get the correct
order.


Time complexity: Each edge is processed exactly once during the construction of the path,
so the algorithm runs in O(n + m), where n is the number of nodes and m is
the number of edges.


Usage: Input consists of multiple test cases.

For each test case:
- n = number of nodes
- m = number of edges

Then m lines follow:
u v (directed edge from u to v)

The input ends when n = 0 and m = 0
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

//Finds an Eulerian path if it exists, otherwise returns an empty vector
std::vector<int> find_euler_path(int n, int m, const std::vector<std::pair<int, int>> &edges)
{
    std::vector<std::vector<std::pair<int, int>>> adj;
    adj.assign(n, std::vector<std::pair<int, int>>());

    std::vector<int> indeg(n, 0);
    std::vector<int> outdeg(n, 0);

    for (int i = 0; i < m; i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back({v, i});
        outdeg[u]++;
        indeg[v]++;
    }

    int start = -1;
    int plus1 = 0;
    int minus1 = 0;

    //Check Eulerian path conditions
    for (int i = 0; i < n; i++)
    {
        if (outdeg[i] - indeg[i] == 1)
        {
            plus1++;
            start = i;
        }
        else
        {
            if (indeg[i] - outdeg[i] == 1)
            {
                minus1++;
            }
            else
            {
                if (indeg[i] != outdeg[i])
                {
                    return {};
                }
            }
        }
    }

    if (!((plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0)))
    {
        return {};
    }

    //If no explicit start node, pick any node with outgoing edges
    if (start == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (outdeg[i] > 0)
            {
                start = i;
                break;
            }
        }
    }

    if (start == -1)
    {
        return {};
    }

    std::vector<bool> used(m, false);
    std::vector<int> idx(n, 0);
    std::vector<int> path;
    std::stack<int> st;

    st.push(start);

    //Hierholzer’s algorithm using a stack
    while (!st.empty())
    {
        int u = st.top();

        //Skip already used edges
        while (idx[u] < (int)adj[u].size() && used[adj[u][idx[u]].second])
        {
            idx[u]++;
        }

        if (idx[u] == (int)adj[u].size())
        {
            //No more edges, add to path
            path.push_back(u);
            st.pop();
        }
        else
        {
            int v = adj[u][idx[u]].first;
            int id = adj[u][idx[u]].second;

            used[id] = true;
            st.push(v);
        }
    }

    //Must use all edges
    if ((int)path.size() != m + 1)
    {
        return {};
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

        std::cin >> n >> m;

        if (!std::cin || (n == 0 && m == 0))
        {
            break;
        }

        std::vector<std::pair<int, int>> edges;

        for (int i = 0; i < m; i++)
        {
            int u;
            int v;

            std::cin >> u >> v;
            edges.push_back({u, v});
        }

        std::vector<int> path = find_euler_path(n, m, edges);

        if (path.empty())
        {
            std::cout << "Impossible\n";
        }
        else
        {
            for (int i = 0; i < (int)path.size(); i++)
            {
                std::cout << path[i];

                if (i + 1 < (int)path.size())
                {
                    std::cout << " ";
                }
            }

            std::cout << "\n";
        }
    }

    return 0;
}
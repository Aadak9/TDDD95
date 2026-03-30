/*
Author: Andreas Nordström, andno773

Problem description: Given an undirected weighted graph, find a minimum spanning tree (MST).
If the graph is not connected, output "Impossible".
Otherwise, output the total weight of the MST and the edges used in it.

Algorithm: Kruskal’s algorithm is used to build the MST.
All edges are sorted by weight, then processed in that order. For each edge,
a Union-Find (Disjoint Set Union) structure is used to check whether the
two endpoints already belong to the same component.
- If they are in different components, the edge is added to the MST and
  the two components are merged.
- If they are already connected, the edge is skipped to avoid cycles.

At the end, if exactly n−1 edges have been selected, the MST is complete.
Otherwise, the graph is disconnected.


Time complexity: The edges are first sorted, which takes O(m log m).

After that, the Union-Find operations are used to check and merge components.
These operations run in almost constant time on average due to path compression
and union by rank.

Overall, the running time is O(m log m).


Usage: Input consists of multiple test cases.

For each test case:
- n = number of nodes
- m = number of edges

Then m lines: u v w (undirected edge between u and v with weight w)

The input ends when n = 0 and m = 0
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u;
    int v;
    int w;
};

vector<int> parent;
vector<int> rnk;

void make_set(int n)
{
    parent.resize(n);
    rnk.resize(n);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int find_set(int v)
{
    if (v == parent[v])
    {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

//Merge two sets if they are different
bool union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);

    if (a == b)
    {
        return false; //already connected
    }

    //Union by rank
    if (rnk[a] < rnk[b])
    {
        swap(a, b);
    }

    parent[b] = a;

    if (rnk[a] == rnk[b])
    {
        rnk[a]++;
    }

    return true;
}

bool cmp_edge(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}

bool compute_mst(int n, vector<Edge> &edges, int &totalCost, vector<pair<int, int>> &result)
{
    sort(edges.begin(), edges.end(), cmp_edge);

    make_set(n);

    totalCost = 0;
    result.clear();

    for (size_t i = 0; i < edges.size(); i++)
    {
        //If edge connects two different components, include it
        if (union_sets(edges[i].u, edges[i].v))
        {
            totalCost += edges[i].w;

            int a = min(edges[i].u, edges[i].v);
            int b = max(edges[i].u, edges[i].v);

            result.push_back({a, b});
        }
    }

    if ((int)result.size() != n - 1)
    {
        return false;
    }

    sort(result.begin(), result.end());

    return true;
}

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }

        vector<Edge> edges;

        for (int i = 0; i < m; i++)
        {
            Edge e;
            cin >> e.u >> e.v >> e.w;
            edges.push_back(e);
        }

        int totalCost;
        vector<pair<int, int>> result;

        bool ok = compute_mst(n, edges, totalCost, result);

        if (!ok)
        {
            cout << "Impossible" << endl;
        }
        else
        {
            cout << totalCost << endl;

            for (size_t i = 0; i < result.size(); i++)
            {
                cout << result[i].first << " " << result[i].second << endl;
            }
        }
    }

    return 0;
}
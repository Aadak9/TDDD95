/*
Author: Andreas Nordström, andno773

Problem description: 

Algorithm: 


Time complexity: 


Usage: 
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

bool union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);

    if (a == b)
    {
        return false;
    }

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
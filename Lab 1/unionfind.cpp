/*
Author: Andreas Nordström, andno773

Problem description: Given a set of N elements and a sequence of Q operations, we maintain a dynamic partition of the elements 
into disjoint sets. There are two types of operations:
1. "= a b": join the sets containing a and b.
2. "? a b": query whether a and b belong to the same set.

Algorithm: - Use Union–Find (Disjoint Set Union) with path compression
- parent[x] stores the representative (root) of x
- find(x) follows parent links to get the root, compressing paths along the way
- same(a, b) checks if a and b have the same root
- unions(a, b) merges two sets by making one root point to the other

Time complexity: Each operation (find, same, union) takes about O(log n) steps.
Doing Q operations takes about O(Q * log n) time in total.

Usage: - First line: N Q
- Next Q lines: operations ("= a b" or "? a b"), where '?' is a query.
- Outputs "yes" or "no" for each query
*/

#include <iostream>
#include <vector>

struct Line
{
    char operation;
    int a;
    int b;
};

//Finds the root of element x.
//Implements path compression: while walking up the tree, each node visited
//is updated to point directly to the root.
int find(int x, std::vector<int>& parent)
{
    if (parent[x] == x)
    {
        return x;
    }
    
    return parent[x] = find(parent[x], parent);
}

//Checks if elements a and b belong to the same set.
bool same(int a, int b, std::vector<int>& parent)
{
    return find(a, parent) == find(b, parent);
}

//Merge the sets containing a and b.
void unions(int a, int b, std::vector<int>& parent)
{

    int root_a = find(a, parent);
    int root_b = find(b, parent);
    if (root_a != root_b)
    {
        parent[root_b] = root_a;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Line line;  
    int N;
    int Q;
    std::cin >> N >> Q;
    //Initially, set each number into a
    //own set
    std::vector<int> parent(N + 1);
    for (int i = 1; i <= N; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < Q; i++)
    {
        std::cin >> line.operation >> line.a >> line.b;
        if (line.operation == '?')
        {
            if (same(line.a, line.b, parent))
            {
                std::cout << "yes" << '\n';
            }
            else
            {
                std::cout << "no" << '\n';
            }
        }
        else if (line.operation == '=')
        {
            unions(line.a, line.b, parent);
        }
    }


    return 0;
}

#include <iostream>
#include <vector>
#include <string>

class FenwickTree
{
private:
    std::vector<long long> tree;
    int n;

public:
    FenwickTree(int size)
    {
        n = size;
        tree.assign(n + 1, 0);
    }

    void add(int index, long long delta)
    {
        index++; 
        while (index <= n)
        {
            tree[index] += delta;
            index += index & -index;
        }
    }

    long long sum(int end)
    {
        long long result = 0;
        while (end > 0)
        {
            result += tree[end];
            end -= end & -end;
        }
        return result;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    FenwickTree bit(n);

    for (int i = 0; i < q; i++)
    {
        std::string op;
        std::cin >> op;

        if (op == "+")
        {
            int idx;
            long long delta;
            std::cin >> idx >> delta;
            bit.add(idx, delta);
        }
        else if (op == "?")
        {
            int end;
            std::cin >> end;
            std::cout << bit.sum(end) << "\n";
        }
    }

    return 0;
}


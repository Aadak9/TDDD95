#include <iostream>
#include <vector>

class FenwickTree
{
private:
    int n;
    std::vector<int> tree;

public:
    FenwickTree(int size)
    {
        n = size;
        tree.assign(n + 1, 0);
    }

    void update(int index, int value)
    {
        while (index <= n)
        {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) const
    {
        int sum = 0;
        while (index > 0)
        {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> pos(n + 1);

    for (int i = 1; i <= n; i++)
    {
        int x;
        std::cin >> x;
        pos[x] = i;
    }

    FenwickTree fw(n);

    for (int i = 1; i <= n; i++)
    {
        fw.update(i, 1);
    }

    int leftValue = 1;
    int rightValue = n;
    int alive = n;

    for (int phase = 1; phase <= n; phase++)
    {
        int value;

        if (phase % 2 == 1)
        {
            value = leftValue;
            leftValue++;
        }
        else
        {
            value = rightValue;
            rightValue--;
        }

        int index = pos[value];
        int currentPos = fw.query(index);

        long long swaps;

        if (phase % 2 == 1)
        {
            swaps = currentPos - 1;
        }
        else
        {
            swaps = alive - currentPos;
        }

        std::cout << swaps << '\n';

        fw.update(index, -1);
        alive--;
    }

    return 0;
}




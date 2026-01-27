/*
Author: Andreas Nordström, andno773

Problem description: An array of length n starts with all zeros. A sequence of operations must be performed 
on the array. Each operation is either "+ idx delta", which increases the element at 
index "idx" by "delta", or "? end", which asks for the sum of elements from index 0 
up to, but not including, "end". All indices are 0-based.

Algorithm: The program uses a Fenwick Tree to perform the operations efficiently. When adding a 
value to an element, the tree updates a set of positions determined by the lowest set 
bit in each index. To compute a prefix sum, the program traverses the tree by repeatedly 
subtracting the lowest set bit from the current index and accumulating the values along 
the path.

Time complexity: Each add or query operation takes O(log n) time. For q operations on an array of size n, 
the total time is O(q log n).

Usage: The first line of input should contain two integers "n" and "q", where "n" is the 
length of the array and "q" is the number of operations to perform. All array 
elements start at zero.
The next "q" lines each describe an operation. An operation is either of the form 
"+ idx delta", which adds "delta" to the element at index "idx", or "? end", which 
requests the sum of elements from index 0 up to, but not including, "end".
All indices are 0-based. For each query of the form "? end", the program prints 
the sum of the specified range on a separate line.
*/



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
        tree.assign(n + 1, 0); //1-indexed
    }

    //Add "delta" to the element at index "index"
    //The tree array is updated along the path defined by the lowest set bit
    //which is the rightmost bit that is 1 in a binary representation of an integer.
    void add(int index, long long delta)
    {
        index++; 
        while (index <= n)
        {
            tree[index] += delta;
            // Bitwise AND between index and its twos complement.
            // This isolates the rightmost 1 bit, which tells how far
            // to move to the next node in the Fenwick Tree.
            index += index & -index; 
        }
    }

    long long sum(int end)
    {
        long long result = 0;
        while (end > 0)
        {
            result += tree[end];
            // Subtract the lowest set bit from end using bitwise AND with its two's complement.
            // This isolates the rightmost 1 bit, which tells how far to move
            // to the next parent node in the Fenwick Tree.
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


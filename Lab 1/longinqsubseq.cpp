/*
Author: Andreas Nordström, andno773

Problem description: Find the longest strictly increasing subsequence in a sequence of integers.
The subsequence does not need to be contiguous. The program outputs the length
of the subsequence and the indices of the elements in it.

Algorithm: This program uses an O(n log n) approach with dynamic tracking.
It uses the following data structures:
- "tail": a vector that stores the smallest possible last value of an increasing subsequence of each length.
- "tailIndex": a vector that stores the index of each value in `tail` in the original array.
- "parent": a vector that stores the previous index in the subsequence for each element.

Step by step:
1. Iterate through each element of the input array.
2. Use binary search (lower_bound) on "tail" to find the first position where the current value can fit.
   - If the value is larger than all elements in "tail", append it.
   - Otherwise, replace the element at that position to keep "tail" minimal.
3. Update "tailIndex" with the current index, and `parent` to remember the previous element in the subsequence.
4. After processing all elements, the length of the LIS is the size of "tail".
5. Backtrack from the last element using the "parent" array to find the indices of the LIS.

Time complexity: Each element is processed using binary search in O(log n) time.
Overall time complexity is O(n log n).
Backtracking takes O(n).

Usage: The input consists of multiple test cases. Each test case has two lines:
1. The first line contains a positive integer n which represents the length of the sequence.
2. The second line contains n integers, each in the range [-2^31, 2^31].
For each test case, the program outputs the length of the LIS and sequence of integers in the LIS.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::pair<int, std::vector<int>> longestIncreasingSubsequence(const std::vector<int>& input)
{
    int n = input.size();
    if (n == 0) 
    {
        return {0, {}};
    }

    std::vector<int> tail;  
    std::vector<int> tailIndex;  
    std::vector<int> parent(n, -1); 

    for (int i = 0; i < n; i++)
    {
        //Find the first position in tail where input[i] can be inserted
        //while keeping tail sorted. If input[i] is larger than all elements in tail
        //, the iterator it will be tail.end().
        auto it = std::lower_bound(tail.begin(), tail.end(), input[i]);
        int pos = it - tail.begin();

        //If input[i] is bigger than all the elements currently in tail
        //than it can increase the LIS.
        if (it == tail.end()) 
        {
            tail.push_back(input[i]);
            tailIndex.push_back(i);
        } 
        //input[i] replaces an element in tail since there is an element in tail
        //that is greater or equal to input[i]. In the case of it being equal it
        //still needs to change and update the position in order for the backtracking
        //to give the right indicies.
        else 
        {
            tail[pos] = input[i];
            tailIndex[pos] = i;
        }
        if (pos > 0) 
        {
            parent[i] = tailIndex[pos - 1];
        }
    }
    int length = tail.size();
    std::vector<int> indices;

    int cur = tailIndex[length - 1];
    while (cur != -1) 
    {
        indices.push_back(cur); 
        cur = parent[cur];
    }

    std::reverse(indices.begin(), indices.end());

    return {length, indices};
}

int main()
{
    int N;

    while (std::cin >> N) 
    {
        std::vector<int> line(N);
        for (int i = 0; i < N; i++) 
        {
            std::cin >> line[i];
        }

        auto result = longestIncreasingSubsequence(line);

        std::cout << result.first << '\n';
        for (int idx : result.second) 
        {
            std::cout << idx << " ";
        }
        std::cout << '\n';
    }
    return 0;
}


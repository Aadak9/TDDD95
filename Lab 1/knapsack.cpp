/*
Author: Andreas Nordström, andno773

Problem description: Given a knapsack with a maximum capacity and a set of items that each has a value and a weight associated to it.
What items should one pick to maximise the total value, given that the total weight of all items is equal or below the 
capacity of the knapsack.

Algorithm: The program uses a dynamic programming approach (bottom-up) to solve the 0/1 Knapsack problem.
dp[i][j] stores the maximum value achievable using the first i items with total weight ≤ j.
For each item, we decide whether to include it or not, updating the DP table.
After filling the table, the chosen items are found by backtracking from the last cell.

Time complexity: Filling the dp table: O(n*capacity), n is the number of items.
Backtracking to find the items: O(n)
Overall: O(n*capacity)

Usage: Assumes the capacity, number of items, values and weight are integers bigger than 0.
*/


#include <iostream>
#include <vector>
#include <algorithm>


struct Object
{
    int value;
    int weight;
};

std::vector<int> knapsack(int capacity, const std::vector<Object>& objects)
{
    int rows = objects.size();
    int columns = capacity;

    std::vector<std::vector<int>> dp(rows + 1, std::vector<int>(columns + 1, 0));

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= columns; j ++)
        {
            if (objects[i-1].weight <= j)
            {
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j - objects[i-1].weight] + objects[i-1].value);
            }
            else
            {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    std::vector<int> chosen_items;
    int i = rows;
    int j = columns;

    while(i > 0 && j > 0)
    {
        if (dp[i][j] != dp[i-1][j])
        {
            chosen_items.push_back(i-1);
            j -= objects[i-1].weight;
        }
        i--;
    }
    std::reverse(chosen_items.begin(), chosen_items.end());
    return chosen_items;
}

int main()
{
    int capacity, n;
    while (std::cin >> capacity >> n) 
    {
        std::vector<Object> objects(n);
        for (int i = 0; i < n; i++)
            std::cin >> objects[i].value >> objects[i].weight;

        std::vector<int> items = knapsack(capacity, objects);

        std::cout << items.size() << '\n';
        for (int idx : items)
            std::cout << idx << " ";
        std::cout << '\n';
    }
}

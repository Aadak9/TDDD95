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
// Function to solve the 0/1 Knapsack problem using dynamic programming.
// Returns a vector of indices of the chosen objects that maximize the total value
// without exceeding the given capacity.
std::vector<int> knapsack(int capacity, const std::vector<Object>& objects)
{
    int rows = objects.size();
    int columns = capacity;

    // Create a DP table with (rows + 1) x (columns + 1) dimensions
    // dp[i][j] will store the maximum value achievable with the first i objects
    // and total weight ≤ j
    std::vector<std::vector<int>> dp(rows + 1, std::vector<int>(columns + 1, 0));

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= columns; j ++)
        {   
            // If the current object's weight fits in the remaining capacity
            if (objects[i-1].weight <= j)
            {
                // Compare the two choices for the current object:
                // 1) Skip it: the maximum value stays the same as without this object (dp[i-1][j])
                // 2) Include it: add its value to the maximum value achievable with the remaining capacity
                // (dp[i-1][j - objects[i-1].weight] + objects[i-1].value)
                // Take the maximum of these two options and store it in dp[i][j]
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j - objects[i-1].weight] + objects[i-1].value);
            }
            else
            {   
                // Current object is too heavy, skip it
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    // Backtrack to find which objects were chosen
    std::vector<int> chosen_items;
    int i = rows;
    int j = columns;

    while(i > 0 && j > 0)
    {
        // If the value changed from the previous row, this object was included
        if (dp[i][j] != dp[i-1][j])
        {
            chosen_items.push_back(i-1);// Add object index to chosen list
            j -= objects[i-1].weight;// Reduce remaining capacity
        }
        i--;// Move to the previous object
    }
    // Reverse the order so that the objects appear in the original input order
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

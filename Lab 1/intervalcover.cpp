/*
Author: Andreas Nordström, andno773

Problem description: Given a target interval [A, B] and a set of intervals, each defined by a start and end point,
determine the minimum number of intervals needed to completely cover the target interval.
If it is impossible to cover the target interval, the program reports "impossible".
The original indices of the chosen intervals should be returned.

Algorithm: The program uses a greedy interval covering strategy.
First, all intervals are sorted by their starting point.
Starting from the beginning of the target interval, the algorithm repeatedly selects
the interval that starts at or before the current coverage point and extends coverage
farthest to the right.
This process continues until the target interval is fully covered or no suitable interval
can be found.

Time complexity: Sorting the intervals: O(n log n), where n is the number of intervals.
Greedy selection (single pass through intervals): O(n).
Overall: O(n log n).

Usage: Assumes interval endpoints are given as real numbers.
Input consists of a target interval, followed by the number of intervals and their endpoints.
*/


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

struct Interval
{
    double A;
    double B;
    int originalIndex;
};

bool compareByStart(const Interval &a, const Interval &b)
{
    return a.A < b.A;
}

std::pair<int, std::vector<int>> cover(const Interval& target, const std::vector<Interval>& list)
{
    double end = target.A;
    int n = list.size();
    std::vector<int> choosenInt;

    // Edge case: target is a single point
    if (target.A == target.B)
    {
        for (int i = 0; i < n; i++)
        {
            if (list[i].A <= target.A && list[i].B >= target.B)
            {
                choosenInt.push_back(list[i].originalIndex);
                return {1, choosenInt};
            }
        }
        return {-1, {}};
    }

    int i = 0;
    while (end < target.B)
    {
        double farthest = end;
        int bestIndex = -1;
        //Consider all intervals that start at or before the current coverage point
        while (i < n && list[i].A <= end)
        {
            //Choose the interval that extends farthest to the right
            if (list[i].B > farthest)
            {
                farthest = list[i].B;
                bestIndex = i;
            }
            i++;
        }

        if (bestIndex == -1)
        {
            return {-1, {}};
        }

        choosenInt.push_back(list[bestIndex].originalIndex);
        end = farthest;
    }

    return {static_cast<int>(choosenInt.size()), choosenInt};
}


int main()
{
    Interval target;
    int n;

    while (std::cin >> target.A >> target.B)
    {
        std::cin >> n;
        std::vector<Interval> intervals(n);

        for (int i = 0; i < n; i++)
        {
            std::cin >> intervals[i].A >> intervals[i].B;
            intervals[i].originalIndex = i; 
        }

        std::sort(intervals.begin(), intervals.end(), compareByStart);

        auto result = cover(target, intervals);

        if (result.first == -1)
        {
            std::cout << "impossible\n";
        }
        else
        {
            std::cout << result.first << "\n";
            for (int idx : result.second)
            {
                std::cout << idx << " ";
            }
            std::cout << "\n";
        }
    }

    return 0;
}


/*
Author: Andreas Nordström, andno773

Problem description: 
Given a string, find the length of the longest substring that appears at least twice.

Algorithm: 
Build the suffix array of the string and then compute the LCP array.
The LCP array stores the longest common prefix between adjacent suffixes
in sorted order. The maximum value in the LCP array is the answer.



Time complexity: 
O(n log n) for suffix array construction, O(n) for LCP.

Usage:
Input:
- Integer n
- String of length n

Output:
- Length of the longest repeated substring (0 if none exists)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//Builds and returns the suffix array of string s.
//sa[i] = starting index of the i-th smallest suffix
std::vector<int> buildSuffixArray(const std::string &s)
{
    int n = s.size();
    std::vector<int> sa(n), rank(n), temp(n);

    for (int i = 0; i < n; i++)
    {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2)
    {
        auto cmp = [&](int i, int j)
        {
            if (rank[i] != rank[j])
            {
                return rank[i] < rank[j];
            }

            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;

            return ri < rj;
        };

        std::sort(sa.begin(), sa.end(), cmp);

        temp[sa[0]] = 0;

        for (int i = 1; i < n; i++)
        {
            temp[sa[i]] = temp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }

        for (int i = 0; i < n; i++)
        {
            rank[i] = temp[i];
        }
    }

    return sa;
}

//Builds the LCP array using Kasais algorithm.
//lcp[i] = LCP of suffixes at sa[i] and sa[i-1]
std::vector<int> buildLCP(const std::string &s, const std::vector<int> &sa)
{
    int n = s.size();
    std::vector<int> rank(n), lcp(n);

    for (int i = 0; i < n; i++)
    {
        rank[sa[i]] = i;
    }

    int h = 0;

    for (int i = 0; i < n; i++)
    {
        if (rank[i] > 0)
        {
            int j = sa[rank[i] - 1];

            //reuse previous LCP to keep this linear
            while (i + h < n && j + h < n && s[i + h] == s[j + h])
            {
                h++;
            }

            lcp[rank[i]] = h;

            if (h > 0)
            {
                h--;
            }
        }
    }

    return lcp;
}

//Returns the length of the longest substring that appears at least twice
int longestRepeatedSubstring(const std::string &s)
{
    std::vector<int> sa = buildSuffixArray(s);
    std::vector<int> lcp = buildLCP(s, sa);

    int ans = 0;

    for (int i = 0; i < (int)lcp.size(); i++)
    {
        if (lcp[i] > ans)
        {
            ans = lcp[i];
        }
    }

    return ans;
}

int main()
{
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int result = longestRepeatedSubstring(s);

    std::cout << result << std::endl;

    return 0;
}
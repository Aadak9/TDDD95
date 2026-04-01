/*
Author: Andreas Nordström, andno773

Problem description: Given a pattern and a text, find all positions where the pattern appears
in the text.
- Print all starting indices of matches
- If there are no matches, print an empty line

Algorithm: The Knuth–Morris–Pratt (KMP) algorithm is used.

The pattern is first preprocessed to build the LPS array (longest prefix
which is also a suffix). This array determines how far the pattern can
be shifted when a mismatch occurs.

The text is then scanned from left to right. When characters match,
the comparison continues. When a mismatch occurs, the LPS array is used
to skip unnecessary comparisons instead of restarting from the next position.

This avoids rechecking characters and ensures efficient matching.


Time complexity: Building the LPS array takes O(m), where m is the pattern length.
Searching takes O(n), where n is the text length.
Total: O(n + m)


Usage: Input consists of multiple test cases.

Each test case:
- First line: pattern
- Second line: text

Input ends at EOF.

For each test case:
- Output all matching positions separated by spaces
*/

#include <iostream>
#include <vector>
#include <string>

/*Builds the LPS (Longest Prefix Suffix) array.
lps[i] = length of the longest proper prefix of pattern[0..i]
which is also a suffix of pattern[0..i]
*/
std::vector<int> buildLPS(const std::string &pattern)
{
    int m = pattern.size();
    std::vector<int> lps(m, 0);

    int len = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            //extend current prefix-suffix match
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            //fallback to shorter prefix
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                //no prefix match possible
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

/*
Finds all starting positions where pattern appears in text
using the KMP algorithm.
*/
std::vector<int> findPositions(const std::string &pattern, const std::string &text)
{
    std::vector<int> result;
    std::vector<int> lps = buildLPS(pattern);

    int i = 0;
    int j = 0;

    int n = text.size();
    int m = pattern.size();

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            //full match found, store starting index
            result.push_back(i - j);
            //continue searching using LPS to avoid rechecking
            j = lps[j - 1];
        }
        else
        {
            if (i < n && text[i] != pattern[j])
            {
                if (j != 0)
                {
                    //jump to next best partial match
                    j = lps[j - 1];
                }
                else
                {
                    //no partial match, move in text
                    i++;
                }
            }
        }
    }

    return result;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string pattern;
    std::string text;

    while (std::getline(std::cin, pattern))
    {
        if (!std::getline(std::cin, text))
        {
            break;
        }

        std::vector<int> positions = findPositions(pattern, text);

        for (int i = 0; i < (int)positions.size(); i++)
        {
            if (i > 0)
            {
                std::cout << " ";
            }
            std::cout << positions[i];
        }

        std::cout << "\n";
    }

    return 0;
}
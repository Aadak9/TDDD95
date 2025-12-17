#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>



std::vector<std::string> suffixArray(std::vector<std::string> input)
{
    return 0;
    //Should return sorted array of all suffixes of a string
    //strcmp??
    //Split string into n-gram?? abba whould be {ab, bb, ba}
    //lexicographic renaming?
}



int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i)
    {
        std::cin >> input;
        std::string trie = suffixTrie(input);
        std:string result = SuffixArray(trie);
        std::cout <<  result << '\n';
    }
    return 0;
}

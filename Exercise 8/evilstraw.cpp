#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

bool is_palindrome_possible(std::string input)
{
    std::unordered_map<char, int> char_freq;
    for (char c : input)
    {
        char_freq[c]++;
    }
    bool even = input.length() % 2 == 0;
    if (even)
    {
        for (auto &p :char_freq)
        {
            if (p.second % 2 != 0)
            {
                return false;
            }
        }
        return true;
    }
    else
    {   
        int oddCounter = 0;
        for (auto &p : char_freq)
        {
            if (p.second % 2 != 0)
            {
                oddCounter++;
            }
        }
        if (oddCounter > 1 || oddCounter == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}

int swaps_to_be_made(std::string input)
{   
    int swaps = 0;
    int n = input.size();

    int left_edge_tracker = 0;
    int right_edge_tracker = n - 1;

    while(left_edge_tracker < right_edge_tracker)
    {
        if (input[left_edge_tracker] == input[right_edge_tracker])
        {
            left_edge_tracker++;
            right_edge_tracker--;
            //continue;
        }
        else
        {
            int k = right_edge_tracker;
            while (k > left_edge_tracker && input[k] != input[left_edge_tracker])
            {
                k--;
            }
            if (k == left_edge_tracker)
            {
                std::swap(input[left_edge_tracker], input[left_edge_tracker + 1]);
                swaps++;
            }
            else
            {
                while (k < right_edge_tracker)
                {
                    std::swap(input[k], input[k + 1]);
                    k++;
                    swaps++;
                }
                left_edge_tracker++;
                right_edge_tracker--;
            }
        }
    }
    

    return swaps;
}


int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; i++)
    {
        std::string input;
        std::getline(std::cin, input);

        if (is_palindrome_possible(input))
        {
            int swaps = swaps_to_be_made(input);
            std::cout << swaps << '\n';
        }
        else
        {
            std::cout << "Impossible" << '\n';
        }
    }
    return 0;
}
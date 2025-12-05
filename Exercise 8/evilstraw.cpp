#include <iostream>
#include <string>
#include <unordered_map>

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

int number_of_switches(std::string input)
{   
    int switches = 0;

    return switches;
}


int main()
{
    int n;
    std::cin >> n;
    std::string input;
    for (int i = 0; i < n; i++)
    {
        std::cin >> input;

        if (is_palindrome_possible(input))
        {
            //int switches = number_of_switches(input);
            //std::cout << switches << '\n';
            std::cout << "Possible" << '\n';
        }
        else
        {
            std::cout << "Impossible" << '\n';
        }
    }
    return 0;
}
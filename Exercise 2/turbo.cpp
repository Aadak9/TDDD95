#include <iostream>
#include <vector>
#include <algorithm>


int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> input(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> input[i];
    }

    for (int phase = 0; phase < n; phase++)
    {   
        int index;
        int target;
        int m = (int)input.size();
        if (phase % 2 == 1)
        {
            index = std::distance(input.begin(), std::max_element(input.begin(), input.end()));
            target = m - 1;
        }
        if (phase % 2 == 0)
        {
            index = std::distance(input.begin(), std::min_element(input.begin(), input.end())); 
            target = 0;
                    
        }
        int swaps = std::abs(index - target);
        std::cout << swaps << "\n";
        input.erase(input.begin() + index);
    }
    return 0;
}

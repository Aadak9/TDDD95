#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void turbosort(std::vector<int>& arr) 
{
    int n = arr.size();
    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());

    std::vector<int> placedIndex(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        placedIndex[arr[i]] = i;
    }

    std::vector<bool> used(n + 1, false);

    for (int phase = 0; phase < n; ++phase) 
    {
        int target = 0;

        if (phase % 2 == 0) 
        {
            for (int i = 0; i < n; ++i) 
            {
                if (!used[sortedArr[i]]) 
                {
                    target = sortedArr[i];
                    break;
                }
            }
        } 
        else 
        {
            for (int i = n - 1; i >= 0; --i) 
            {
                if (!used[sortedArr[i]]) 
                {
                    target = sortedArr[i];
                    break;
                }
            }
        }

        int currentPos = placedIndex[target];
        int finalPos = 0;
        for (int i = 0; i < n; ++i) 
        {
            if (sortedArr[i] == target) 
            {
                finalPos = i;
                break;
            }
        }

        int swaps = 0;

        while (currentPos < finalPos) 
        {
            std::swap(arr[currentPos], arr[currentPos + 1]);
            placedIndex[arr[currentPos]] = currentPos;
            placedIndex[arr[currentPos + 1]] = currentPos + 1;

            currentPos++;
            swaps++;
        }

        while (currentPos > finalPos) 
        {
            std::swap(arr[currentPos], arr[currentPos - 1]);
            placedIndex[arr[currentPos]] = currentPos;
            placedIndex[arr[currentPos - 1]] = currentPos - 1;

            currentPos--;
            swaps++;
        }

        used[target] = true;
        std::cout << swaps << std::endl;
    }
}

int main() 
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) 
    {
        std::cin >> arr[i];
    }

    turbosort(arr);

    return 0;
}






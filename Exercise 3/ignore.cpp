#include <iostream>
#include <string>
#include <vector>

bool isValid(int number)
{
    if (number == 0)
    {
        return true;
    }

    while (number > 0)
    {
        int digit = number % 10;
        if (digit == 3 || digit == 4 || digit == 7)
        {
            return false;
        }
        number /= 10;
    }

    return true;
}

std::string upsideDown(int number)
{
    std::string result = "";
    std::vector<int> mapping(10);
    mapping[0] = 0;
    mapping[1] = 1;
    mapping[2] = 2;
    mapping[5] = 5;
    mapping[6] = 9;
    mapping[8] = 8;
    mapping[9] = 6;

    if (number == 0)
    {
        return "0";
    }

    while (number > 0)
    {
        int digit = number % 10;
        result = char('0' + mapping[digit]) + result;
        number /= 10;
    }

    return result;
}

std::string getKthNumber(int k)
{
    int count = 0;
    int current = 1;

    while (true)
    {
        if (isValid(current))
        {
            count++;
            if (count == k)
            {
                return upsideDown(current);
            }
        }
        current++;
    }
}

int main()
{
    int k;

    while (std::cin >> k)
    {
        std::string number = getKthNumber(k);
        std::cout << number << "\n";
    }

    return 0;
}



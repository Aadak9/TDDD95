#include <iostream>
#include <string>
#include <vector>
//Use positional counting instead of counting every number, otherwise it will be to slow and not pass the time limit.
static const int firstDigits[6] = {1, 2, 5, 6, 8, 9};
static const int otherDigits[7] = {0, 1, 2, 5, 6, 8, 9};
static const char upsideDownMap[10] = {'0','1','2','?','?','5','9','?','8','6'};

std::string getNormalNumber(unsigned long long k)
{
    unsigned long long length = 1;
    unsigned long long count = 6;

    while (k > count)
    {
        k -= count;
        length++;
        count *= 7;
    }

    k--; 
    std::vector<int> digits(length);
    digits[0] = firstDigits[k / (count / 6)];
    unsigned long long rem = k % (count / 6);
    unsigned long long block = count / 6;

    for (size_t i = 1; i < length; i++)
    {
        block /= 7;
        digits[i] = otherDigits[rem / block];
        rem %= block;
    }

    std::string number;
    for (int d : digits)
    {
        number.push_back('0' + d);
    }

    return number;
}

std::string upsideDown(const std::string &number)
{
    std::string result;
    for (int i = number.size() - 1; i >= 0; i--)
    {
        result.push_back(upsideDownMap[number[i] - '0']);
    }
    return result;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned long long k;
    while (std::cin >> k)
    {
        std::string normal = getNormalNumber(k);
        std::cout << upsideDown(normal) << "\n";
    }

    return 0;
}




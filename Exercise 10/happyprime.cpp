#include <iostream>
#include <cmath>
#include <unordered_set>

bool isPrime(int input) 
{
    if (input < 2) 
    {    
        return false;
    }
    for (int i = 2; i <= input / 2; ++i) 
    {
        if (input % i == 0) 
        {
            return false;
        }
    }
    return true;
}

int digitSum(int input)
{
    int sum = 0;
    while (input != 0)
    {
        int last_digit = input % 10;
        sum += pow(last_digit, 2);
        input /= 10;
    }
    return sum;
}

bool isHappy(int input)
{
    std::unordered_set<int> seen;
    int sum = digitSum(input);
    while (sum != 1 && seen.find(sum) == seen.end())
    {
        seen.insert(sum);
        sum = digitSum(sum);
    }
    return sum == 1;
}

int main()
{

    int P;
    std::cin >> P;

    for (int i = 0; i < P; i++)
    {
        int K;
        int m;
        std::cin >> K >> m;
        if (isPrime(m) && isHappy(m))
        {
            std::cout << K << ' ' << m << ' ' << "YES" << '\n';
        }
        else
        {
            std::cout << K << ' ' << m << ' ' << "NO" << '\n';
        }
    }
    return 0;
}
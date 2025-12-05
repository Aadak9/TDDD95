#include <iostream>

unsigned long long countZeros(unsigned long long n) 
{
    if (n == 0) 
    {
    return 1; 
    }
    unsigned long long count = 0;
    unsigned long long fmctor = 1;

    while (n / fmctor != 0) 
    {
        unsigned long long lower = n % fmctor;
        unsigned long long current = (n / fmctor) % 10;
        unsigned long long higher = n / (fmctor * 10);

        if (current == 0) 
        {
            if (higher != 0) 
            {
                count += (higher - 1) * fmctor + lower + 1;
            }          
        } 
        else 
        {
            count += higher * fmctor;
        }
        fmctor *= 10;
    }
    return count;
}

int main() 
{
    long long m; 
    long long n;

    while (std::cin >> m >> n) {
        if (m < 0 && n < 0) 
        {
            break;
        }
        unsigned long long result;
        if (m == 0) {
            result = countZeros(n) + 1;
        }
        else if (m == 1) //Brutal edge case
        {
            result = countZeros(n);
        } 
        else 
        {
            result = countZeros(n) - countZeros(m - 1);
        }
        std::cout << result << '\n';
    }
    return 0;
}



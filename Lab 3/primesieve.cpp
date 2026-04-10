/*
Author: Andreas Nordström, andno773

Problem description: 
Given an integer n and q queries, determine how many primes are ≤ n,
and for each query x, check whether x is a prime number.

Algorithm: 
Use the Sieve of Eratosthenes to mark all primes up to n.
Then store prime information in a boolean array for O(1) queries.
Count primes by scanning the array once after the sieve.



Time complexity: 
O(n log log n) for building the sieve, O(n) for counting primes,
and O(1) per query.

Usage:
Input:
- Integer n
- Integer q
- q lines, each containing an integer x

Output:
- First line: number of primes ≤ n
- Next q lines:
  - 1 if x is a prime number
  - 0 otherwise

*/

#include <iostream>
#include <vector>

class Sieve
{
private:
    std::vector<bool> isPrime;
    int limit;

public:
    Sieve(int n)
    {
        limit = n;
        isPrime.assign(n + 1, true);//assume all numbers are prime initially

        if (n >= 0)
        {
            isPrime[0] = false;
        }
        if (n >= 1)
        {
            isPrime[1] = false;
        }

        //standard sieve: mark multiples of each prime as composite
        for (int i = 2; i * i <= n; i++)
        {
            if (isPrime[i])
            {
                for (int j = i * i; j <= n; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }
    }

    bool query(int x) const
    {
        //check bounds first to avoid invalid access
        return (x >= 0 && x <= limit && isPrime[x]);
    }

    int countPrimes() const
    {
        int cnt = 0;

        //count all numbers still marked as prime
        for (int i = 2; i <= limit; i++)
        {
            if (isPrime[i])
            {
                cnt++;
            }
        }

        return cnt;
    }
};

int main()
{
    int n, q;
    std::cin >> n >> q;

    Sieve sieve(n);

    std::cout << sieve.countPrimes() << std::endl;

    for (int i = 0; i < q; i++)
    {
        int x;
        std::cin >> x;

        if (sieve.query(x))
        {
            std::cout << 1 << std::endl;
        }
        else
        {
            std::cout << 0 << std::endl;
        }
    }

    return 0;
}
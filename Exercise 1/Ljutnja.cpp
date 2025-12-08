#include <iostream>
#include <map>
#include <cstdint>

unsigned long long calculateAnger(long long M, std::map<int, unsigned long long> freq) 
{
    int N = 0;
    for (auto &p : freq) 
    {
        N += p.second;
    }
    if (freq.count(0))
    {
        N -= freq[0];
    }
    unsigned long long totalWish = 0;
    for (auto &p : freq)
    {
        totalWish += p.first * p.second;
    }
    unsigned long long toRemove = totalWish - M;

    unsigned long long anger = 0;

    int level = 0;         
    int nextLevel = 1;     

    while (true) 
    {
        if (toRemove <= (unsigned long long)N) 
        {
            anger += toRemove * nextLevel * nextLevel;
            anger += (N - toRemove) * level * level;
            break;
        }
        level += toRemove / N;
        toRemove %= N;

        
        for (int w = nextLevel; w <= level; w++) 
        {
            if (freq.count(w)) 
            {
                unsigned long long cnt = freq[w];

                anger += cnt * (unsigned long long)w * w;  

                N -= cnt;                     
                toRemove += (level - w) * cnt; 
            }
        }

        nextLevel = level + 1;
    }

    return anger;
}

int main() 
{
    int M, N;
    std::cin >> M >> N;
    std::map<int, unsigned long long> freq;
    for (int i = 0; i < N; i++) 
    {
        int k;
        std::cin >> k;
        freq[k]++;
    }
    std::cout << calculateAnger(M, freq) << "\n";
    return 0;
}


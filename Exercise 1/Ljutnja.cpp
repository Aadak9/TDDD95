#include <iostream>
#include <map>
#include <cstdint>

int main() {
    int M;   // total candies
    int N;   // number of children
    std::cin >> M >> N;

    // freq[w] = number of children who want w candies
    std::map<int, unsigned long long> freq;

    for (int i = 0; i < N; i++) {
        int k;
        std::cin >> k;
        freq[k]++;
    }

    // Remove children wanting 0 candies
    if (freq.count(0))
        N -= freq[0];

    // Calculate total amount of candy wished
    unsigned long long totalWish = 0;
    for (auto &p : freq)
        totalWish += p.first * p.second;

    // Amount we must remove
    unsigned long long toRemove = totalWish - M;

    unsigned long long anger = 0;

    int level = 0;         // current equalized distribution level
    int nextLevel = 1;     // next wish level boundary

    while (true) {

        // If we can finish within one level difference
        if (toRemove <= (unsigned long long)N) {
            anger += toRemove * nextLevel * nextLevel;
            anger += (N - toRemove) * level * level;
            break;
        }

        // Raise the equalized level
        level += toRemove / N;
        toRemove %= N;

        // Adjust children whose wish is below the new equal level
        for (int w = nextLevel; w <= level; w++) {
            if (freq.count(w)) {
                unsigned long long cnt = freq[w];

                anger += cnt * (unsigned long long)w * w;  // fixed anger part

                N -= cnt;                     // those kids are done
                toRemove += (level - w) * cnt; // adjust missing amount
            }
        }

        nextLevel = level + 1;
    }

    std::cout << anger << "\n";
    return 0;
}

#include <iostream>
#include <cmath>

int main() {
    int n;
    while (std::cin >> n) 
    {
        if (n == 0) 
        {
            break; 
        }
        if (n == 1 || n == -1) 
        {
            std::cout << 1 << "\n";
            continue;
        }
        long long absn;
        if (n < 0)
        {
            absn = -(long long)n;
        }           
        else
        {
            absn = (long long)n;
        }
        int max_k = 1;
        for (int k = 31; k >= 2; k--) 
            { 
                if (n < 0 && k % 2 == 0) 
                {
                    continue;
                }
                double root = std::pow(absn, 1.0 / k);               
                long long a = std::llround(root);
                long long power = 1;
                for (int i = 0; i < k; i++) 
                {
                    power *= a;
                    if (power > absn)
                    {
                        break;
                    }
                }
                if (power == absn) 
                {
                    max_k = k;
                    break;
                }
            }        
        std::cout << max_k << "\n";
    }
    return 0;
}

/*
Author: Andreas Nordström, andno773

Problem description: Multiply two polynomials given by their coefficients. 
Input: degree and coefficients of each polynomial. 
Output: degree and coefficients of the resulting polynomial.

Algorithm: - FFT:
  - Split the polynomial into even and odd coefficients.
  - Recursively compute FFT for each half.
  - Combine the results using complex roots of unity.
  - If doing inverse FFT, divide all coefficients by n.
- Multiplication:
  - Copy the integer coefficients into complex vectors.
  - Pad them to the next power of 2.
  - Compute FFT for both polynomials.
  - Multiply the results point by point.
  - Compute inverse FFT to get back coefficients.
  - Round the real parts to integers to get the final polynomial.

Time complexity: O(n log n) using FFT, where n is the next power of 2 ≥ deg1 + deg2 + 1.

Usage: All coefficients are integers. Read from standard input and print the resulting polynomial to standard output.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using cd = std::complex<double>;
const double PI = acos(-1);

//Recursive FFT 
void fft(std::vector<cd> & a, bool invert) 
{
    //If vector has 1  element, FFT is itself
    int n = a.size();
    if (n == 1)
    {
        return;
    }

    std::vector<cd> a0(n / 2);
    std::vector<cd> a1(n / 2);
    for (int i = 0; 2 * i < n; i++) 
    {
        a0[i] = a[2 * i]; //Even index
        a1[i] = a[2 * i + 1]; //Odd index
    }
    fft(a0, invert);
    fft(a1, invert);

    // Compute the angle for the current level of FFT
    // 2*PI/n gives the spacing between the n-th roots of unity on the unit circle
    // If we are doing inverse FFT (invert == true), we need to rotate clockwise, so we use a negative angle
    // If forward FFT (invert == false), we rotate counter-clockwise using a positive angle
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w = cd(1, 0); // initial root
    cd wn = cd(std::cos(ang), std::sin(ang)); // principal n-th root of unity

    // Combine results from even and odd halves
    for (int i = 0; 2 * i < n; i++) 
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) 
        {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
         w *= wn;
    }
}

//Multiply two polynomials using FFT
std::vector<int> multiplication(const std::vector<int> &poly1, const std::vector<int> &poly2)
{
{
    int sizeA = poly1.size();
    int sizeB = poly2.size();
    int resultSize = sizeA + sizeB - 1;

    int n = 1;
    while (n < resultSize)
    {
        n <<= 1;
    }
  
    // Copy coefficients into complex vectors and pad with zeros
    std::vector<cd> Fpoly1(n);
    std::vector<cd> Fpoly2(n);

    for (int i = 0; i < sizeA; i++)
    {
        Fpoly1[i] = poly1[i];
    }

    for (int i = 0; i < sizeB; i++)
    {
        Fpoly2[i] = poly2[i];
    }

    fft(Fpoly1, false);
    fft(Fpoly2, false);

    for (int i = 0; i < n; i++)
    {
        Fpoly1[i] *= Fpoly2[i];
    }

    // Inverse FFT to get back coefficients
    fft(Fpoly1, true);

    std::vector<int> result(resultSize);

    // Round the real parts to get final integer coefficients
    for (int i = 0; i < resultSize; i++)
    {
        
        result[i] = std::round(Fpoly1[i].real());
    }

    return result;
}
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    int degPoly1;
    std::cin >> degPoly1;

    std::vector<int> Poly1(degPoly1 + 1);
    for (int i = 0; i <= degPoly1; ++i)
    {
        std::cin >> Poly1[i];
    }

    int degPoly2;
    std::cin >> degPoly2;

    std::vector<int> Poly2(degPoly2 + 1);
    for (int i = 0; i <= degPoly2; i++)
    {
        std::cin >> Poly2[i];
    }

    int totalDegree = degPoly1 + degPoly2;
    std::vector<int> result = multiplication(Poly1, Poly2);

    std::cout << totalDegree << '\n';
    for (int i = 0; i <= totalDegree; i++)
    {
        std::cout << result[i];

        if (i != totalDegree)
        {
            std::cout << " ";
        }
    }

    return 0;
}
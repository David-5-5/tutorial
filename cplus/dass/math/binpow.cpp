#include <iostream>

using namespace std;

/**
 * Binary exponentiation, is a trick to calculate a^n in the time of O(logN),
 * while the calculation of brute force takes the time of O(N).
 */
long long binpow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

/**
 * According to Fermat's theorem, if m is a prime number, 
 * we can compute x^{n mod (m-1)} to speed up the algorithm
 */
long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main()
{
    cout << " 23 ^ 102222 = " << binpow(23, 1000222) << endl;
    cout << " 23 ^ 102222 % 2345 = " << binpow(23, 1000222, 2345) << endl;
}

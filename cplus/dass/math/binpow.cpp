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
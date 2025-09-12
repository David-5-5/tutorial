#include <bits/stdc++.h>
using namespace std;

// Rabin-Karp 字符串编码
class Solution {
public:
    string longestPrefix(string s) {
        // Rabin karp 变型 - 蒙特卡洛方法 双 hash
        int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
        int base1 = 401, base2 = 701;
        long long bm1 = 1, bm2 = 1;        
        int n = s.length();

        auto prefixHash = [&](pair<long long, long long>& hash, int i) -> void {
            hash.first = (hash.first * base1 + s[i]) % mod1;
            hash.second = (hash.second * base2 + s[i]) % mod2;
        };

        auto suffixHash = [&](pair<long long, long long>& hash, int i) -> void {

            hash.first = (bm1 * s[i]  + hash.first) % mod1;
            hash.second = (bm2 * s[i] + hash.second) % mod2;
            bm1 = (bm1 * base1) % mod1; bm2 = (bm2 * base2) % mod2; 
        };

        pair<long long, long long> pHash = {0, 0}, sHash = {0, 0}; int len = -1;
        for (int i=0; i<n-1; ++i) {
            prefixHash(pHash, i); suffixHash(sHash, n - i - 1);
            if (pHash == sHash) len = i;
        }

        return s.substr(0, len+1);

    }

    string longestPrefix2(string s) {
        // Rabin karp 变型 - 单hash
        int mod = 1e9 + 7; int base = 401; long long bm = 1;
        int n = s.length();

        auto prefixHash = [&](long long& hash, int i) -> void {
            hash = (hash * base + s[i]) % mod;
        };

        auto suffixHash = [&](long long& hash, int i) -> void {

            hash = (bm * s[i]  + hash) % mod;
            bm = (bm * base) % mod;
        };

        long long pHash = 0, sHash = 0; int len = -1;
        for (int i=0; i<n-1; ++i) {
            prefixHash(pHash, i); suffixHash(sHash, n - i - 1);
            if (pHash == sHash) len = i;
        }

        return s.substr(0, len+1);

    }


};
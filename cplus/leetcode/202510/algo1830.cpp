#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MX = 3001;   // 根据取值范围进行变更

long long pow(long long base, int exp)
{
    base %= MOD;
    long long res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

long long fac[MX+1];        // n!
long long inv_fac[MX+1];    // n! 的逆元
auto init = [] {
    fac[0] = 1;
    for (int i=1; i<MX+1; i++) {
        fac[i] = fac[i-1] * i % MOD;
    }
    inv_fac[MX] = pow(fac[MX], MOD-2);
    for (int i=MX; i; i--) {
        inv_fac[i-1] = inv_fac[i] * i % MOD;
    }
    return 0;
}();

// 数学算法 - 组合数学 - 2.2 组合计数
class Solution {
public:
    int makeStringSorted(string s) {
        int n = s.length(); vector<int> cnt(26);
        for (auto ch : s) cnt[ch-'a'] ++;
        long long ans = 0;
        for (int i=0; i<n-1; ++i) {
            char ch = s[i];
            long long rank = 0; for (int j=0; j<ch-'a'; ++j) rank += cnt[j];
            rank = rank * fac[n-1-i] % MOD;
            for (auto v: cnt) rank = rank * inv_fac[v] % MOD;
            ans = (ans + rank) % MOD;
            cnt[ch-'a'] --;
        }
        return ans;
    }
};
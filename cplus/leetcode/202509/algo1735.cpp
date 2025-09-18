#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
int lpf[N];

// 组合数的区间
const int MOD = 1e9+ 7;
int MAXN = 1e4 + 14;
int MAXK = 14;
vector<vector<int>> c(MAXN, vector<int>(MAXK));

int init = [] {
    memset(lpf, 0, sizeof(lpf));

    for (int i = 2; i < N; ++i) {      
        if (lpf[i] == 0) { // 质数
            for (int j = i; j < N; j += i) {
                if (lpf[j] == 0) lpf[j] = i;   // 质数 x 的 lpf(x) == x
            }
        }
    }

    // 本题计算组合数
    for (int i=1; i<MAXN; ++i) {
        c[i][0] = 1;
        for (int j = 1; j<min(MAXK, i+1); ++j) {
            c[i][j]= (c[i-1][j] + c[i-1][j-1]) % MOD;
        }
    } 
    return 0;
}();

// prime_factor(45) = {{3,2}, {5,1}} 45 = 3^2 * 5^1
// prime_factor(16) = {{2,4}} = 2^4
vector<pair<int, int>> prime_factors(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = lpf[x], e = 1;
        for (x/=p; x % p == 0; x /= p) e ++;
        res.emplace_back(p, e);
    }
    return res;
}

// 数学算法 - 数论 - 1.3 质因数分解
class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        vector<int> ans;
        for (const auto& q: queries) {
            auto n = q[0], comp = q[1];
            int tot = 1;
            for (auto& [_, k] : prime_factors(comp)) {
                tot = ((long long)tot * c[n+k][k]) % MOD;
            }
            ans.emplace_back(tot);
        }
        return ans;
    }
};
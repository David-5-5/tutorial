#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 基本不等式
class Solution {
    const long long MOD = 1e9 + 7;

    // 快速幂 模板
    long long qpow(long long base, long exponent) {
        base %= MOD;
        long long ans = 1;
        while (exponent > 0) {
            if (exponent & 1) ans = ans * base % MOD;
            base = base * base % MOD;
            exponent >>= 1;
        }
        return ans;
    }

public:
    int minNonZeroProduct(int p) {
        // 自行解答，快速幂
        // long long 移位单独写，与 +/- int 分开写
        long long k = (long long) 1 << p; 
        return (k - 1) % MOD * qpow(k-2, (k-2)>> 1) % MOD;
    }
};

int main() {
    Solution solution;
    cout << solution.minNonZeroProduct(55) << endl;
}

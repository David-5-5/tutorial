#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long qpow(long long base, int exp)
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

// 数学算法 - 组合数学 - 2.5 贡献法
class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long ans = 0;
        vector<int> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; i++) {
            pow2[i] = pow2[i - 1] * 2 % MOD; // 预处理 2 的幂次
        }
   
        for (int i = 0; i < n; ++i) {
            // ans += (qpow(2,i) - qpow( 2,n - 1 - i)) * nums[i];
            ans += long(pow2[i] - pow2[n - 1 - i]) * nums[i];
            ans %= MOD;
        }
        // 确保结果非负
        return (ans + MOD) % MOD;
    }
};

int main() {
    vector<int> nums = {2,1,3,2,1,3};
    cout << Solution().sumSubseqWidths(nums) << endl;
}
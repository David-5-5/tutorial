#include <bits/stdc++.h>
using namespace std;

// 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        // 参考题解，执行一次操作，平方和越大。
        const int mod = 1e9 + 7;
        vector<int> cnt(32);
        for (auto& val: nums) {
            for (int i=0; i<32; i++) {
                if ((val >> i) & 1) cnt[i]++;
            }
        }
        int ans = 0;
        for (int _=0; _<k; _++) {
            int cur = 0;
            for (int i=0; i<32; i++) {
                if (cnt[i]) {
                    cur += 1 << i;
                    cnt[i] --;
                }
            }
            ans = (ans + (long long) cur * cur) % mod;
        }
        return ans;

    }
};
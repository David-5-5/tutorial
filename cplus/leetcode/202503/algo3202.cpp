#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // 参考题解
        // (a+b)modk=(b+c) mod k 移项得 (a+b−(b+c)) mod k=0  化简得 (a−c) mod k = 0
        // 有效子序列的奇数项都关于模 k 同余，偶数项都关于模 k 同余
        // 寻找一个最长的子序列，满足子序列奇数项都相同，偶数项都相同
        // 我们可以在「最后两项模 k 分别为 x 和 y 的子序列」的末尾添加 nums[i]，
        // 那么「最后两项模 k 分别为 y 和 x 的子序列」的长度会增加 1，
        // 状态转移方程 f[y][x]=f[x][y]+1

        vector<vector<int>> dp(k, vector<int>(k));
        int ans = 0;
        for (auto x : nums) {
            x %= k;
            for (int y=0; y<k; y++) {
                dp[y][x] = dp[x][y] + 1;
                ans = max(ans, dp[y][x]);
            }
        }

        return ans;

    }
};
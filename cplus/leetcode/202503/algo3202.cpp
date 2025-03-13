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
        // 状态转移方程 dp[y][x]=dp[x][y]+1

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

    int maximumLength2(vector<int>& nums, int k) {
        // 参考题解
        // 枚举余数，余数确定的情况下 m， 最后一项为 x
        // 则前一项的同余值也确定为  (x - m + k)  % k
        // 状态转移方程为 dp[x]=dp[(m-x+k)%k]+1
        int ans = 0;
        for (int m=0; m<k; m++) {
            vector<int> dp(k);
            for (auto x : nums) {
                x %= k;
                dp[x] = dp[(m - x + k) % k] + 1;
                ans = max(ans, dp[x]);
            }
        }

        return ans;  

    }    

};
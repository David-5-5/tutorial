#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 合法子序列 DP
class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        // 自行解答 
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> pos;
        vector<int> dp(n, 1);
        pos[nums[0]] = 0;

        int ans = 1;
        for (int i = 1; i < n; i++) {
            int x = (int) sqrt(nums[i]);
            if (x*x == nums[i] && pos.count(x)) {
                dp[i] = dp[pos[x]] + 1;
            }
            pos[nums[i]] = i;
            ans = max(ans, dp[i]);
        }
        return ans>1?ans:-1;
    }

    int longestSquareStreak2(vector<int>& nums) {
        // 参考题解 未注意到 nums[i] >= 2, 不存在多个 1，取 nums的集合即可
        unordered_set s(nums.begin(), nums.end());
        int ans = 0;
        for (auto x : s) {
            int cnt = 0;
            while (s.count(x)) {
                cnt ++;
                if (x > 317) break;   // 数据范围 floor(sqrt(100000))
                x *= x;
            }
            ans = max(ans, cnt);
        }

        return ans > 1? ans : -1;
    }

};  
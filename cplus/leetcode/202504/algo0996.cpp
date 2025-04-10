#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.2 排列型 - 相邻相关
// 2023. 7 python
// 2025. 4 复习 自行解答
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, int> cnt;
        for (auto& k: nums) cnt[k] ++;        

        auto is_square = [&] (int i, int j) -> bool {
            if (i == n) return true;
            int sq = int(sqrt(nums[i] + nums[j]));
            return sq * sq == (nums[i] + nums[j]);
        };

        vector<vector<int>> memo(n+1, vector<int>(1<<n, -1));
        auto dfs = [&] (this auto&& dfs, int i, int state) -> int {
            // cout << i << ", " << state << endl;
            if (state == 0) return 1;
            auto& res = memo[i][state];
            if (res != -1) return res;
            res = 0;
            for (int j=0; j<n; j++) 
                if (((state >> j) & 1) && is_square(i, j)) 
                    res += dfs(j, state - (1 << j));

            return res;
        };

        // 对相同元素，除以排列数，得到组合数
        int ans = dfs(n, (1<<n)-1);
        cout << ans << endl;
        for (auto& [_, v]: cnt) for (int t=2; t<=v; ++t)
            ans /= t;

        return ans;
    }
};
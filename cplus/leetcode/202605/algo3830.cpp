#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int longestAlternating(vector<int>& nums) {
        // 自行解答 前后缀分解 
        int ans = 1, n = nums.size();

        vector<pair<int, int>> suffix(n);
        suffix[n-1] = {0, 1};
        for (int i=n-2; i>=0; i--) {
            if (nums[i] == nums[i+1]) {
                suffix[i] = {0, 1};
            } else {
                suffix[i].first = nums[i] < nums[i+1]?1:-1;
                if (suffix[i].first != suffix[i+1].first) suffix[i].second = suffix[i+1].second + 1;
                else suffix[i].second = 2;
            }
            ans = max(ans, suffix[i].second);
        }

        pair<int, int> pre = {0, 1};
        for (int i=1; i<n-1; i++) {
            if (nums[i-1] != nums[i+1]) {
               auto skip = nums[i-1] < nums[i+1]?1:-1;

                if (pre.first != skip && skip != suffix[i+1].first)
                    ans = max(ans, pre.second + suffix[i+1].second);
                else if (skip != suffix[i+1].first) 
                    ans = max(ans, suffix[i+1].second + 1);
                else if (pre.first != skip)
                    ans = max(ans, pre.second + 1);
            }

            if (nums[i-1] == nums[i]) pre = {0, 1};
            else {
                auto cur = nums[i-1] < nums[i]?1:-1;
                if (pre.first != cur) pre.second += 1, pre.first = cur;
                else pre.second = 2;
            }
        }
        return ans;     
    }

    int longestAlternating2(vector<int>& nums) {
        // 状态机DP 记忆化搜索 translate from python
        int n = nums.size();
        if (n == 0) return 0;

        // 记忆化数组：i, can_del(0/1), inc(0/1)
        int memo[100005][2][2];
        memset(memo, -1, sizeof(memo));

        auto dfs = [&](this auto&& dfs, int i, bool can_del, bool inc) -> int {
            if (i == 0) return 1;

            int c_del = can_del ? 1 : 0;
            int c_inc = inc ? 1 : 0;
            if (memo[i][c_del][c_inc] != -1) {
                return memo[i][c_del][c_inc];
            }

            int res = 1;
            // 不删除前一个
            if (nums[i-1] != nums[i] && (nums[i-1] < nums[i]) == inc) {
                res = dfs(i-1, can_del, !inc) + 1;
            }
            // 可以删除，且跳过前一个
            if (can_del && i > 1 && nums[i-2] != nums[i] && (nums[i-2] < nums[i]) == inc) {
                res = max(res, dfs(i-2, false, !inc) + 1);
            }

            return memo[i][c_del][c_inc] = res;
        };

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, max(dfs(i, true, true), dfs(i, true, false)));
        }

        return ans;
    }    

};

int main() {
    vector<int> nums = {1,1,1};
    cout << Solution().longestAlternating(nums) << endl;
}
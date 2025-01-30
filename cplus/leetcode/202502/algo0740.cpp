#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 打家劫舍
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        // 记忆化搜索
        unordered_map<int, int> cnt;
        for (auto v:nums) cnt[v] ++;    // 相同元素分组计数
        vector<pair<int, int>> group(cnt.begin(), cnt.end()); // 将map -> vector
        sort(group.begin(), group.end()); // 按照第一个元素排序
       
        int n = group.size();
        vector<int> memo(n, -1);

        function<int(int)> dfs = [&](int i) -> int {
            if (i < 0) return 0;
            if (memo[i] != -1)  return memo[i];

            int score = group[i].first * group[i].second;
            if (i && group[i].first==group[i-1].first+1)
                memo[i] = max(dfs(i-1), dfs(i-2) + score);
            else memo[i] = dfs(i-1) + score;

            return memo[i];
        };

        return dfs(n-1);
        
    }
};
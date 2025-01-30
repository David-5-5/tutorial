#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 打家劫舍
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        // 自行解答 同 740
        unordered_map<int, int> cnt;
        for (auto v:power) cnt[v] ++;    // 相同元素分组计数
        vector<pair<int, int>> group(cnt.begin(), cnt.end()); // 将map -> vector
        sort(group.begin(), group.end()); // 按照第一个元素排序
       
        int n = group.size();
        vector<long long> memo(n, -1);
        
        
        function<long long(int)> dfs = [&](int i) -> long long {// 超时
        // auto dfs = [&](this auto&& dfs, int i) -> long long { 
            if (i < 0) return 0;
            if (memo[i] != -1)  return memo[i];

            long long score = (long long)group[i].first * group[i].second;
            if (i>1 && group[i].first==group[i-2].first+2)
                memo[i] = max(dfs(i-2), max(dfs(i-1), dfs(i-3) + score));
            else if (i && (group[i].first==group[i-1].first+1 || group[i].first==group[i-1].first+2))
                memo[i] = max(dfs(i-1), dfs(i-2) + score);
            else memo[i] = dfs(i-1) + score;

            return memo[i];
        };

        return dfs(n-1);         
    }
};
#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：跳跃游戏
class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        // 自行解答
        int n = arr.size();

        // 从右到左遍历 arr，严格递增，相同的值取最小下标
        vector<pair<int, int>> suffix; suffix.emplace_back(arr[n-1], n-1);
        // 数据和作用详见下文注释
        vector<int> lessThan(n, n), greatThan(n, n); 
        
        int ans = 1;
        vector memo(n, vector<int>(2, -1));
        memo[n-1][0] = 1, memo[n-1][1] = 1;
        for (int k=n-2; k>=0; --k) {
            // 从后遍历，计算 arr[k] 小于等于后缀中最小的值
            auto it = ranges::lower_bound(suffix, arr[k], {}, &pair<int, int>::first);
            if (it != suffix.end())
                lessThan[k] = it->second;

            // 计算 arr[k] 大于等于后缀中的最大的值
            if (it != suffix.end() && it->first == arr[k])
                greatThan[k] = it->second;
            else if (it != suffix.begin()) {greatThan[k] = (--it)->second; ++it;}
            // 将当前元素更新或插入后缀中
            if (it != suffix.end() && it->first == arr[k]) it->second = k;
            else suffix.insert(it, {arr[k], k});

            auto dfs = [&] (this auto&& dfs, int i, int j) -> bool {
                if (memo[i][j] != -1) return memo[i][j];
                if (j)  {   // 奇数步
                    if (lessThan[i] == n) return memo[i][j] = 0;
                    else return memo[i][j] = dfs(lessThan[i], j^1);
                } else {
                    if (greatThan[i] == n) return memo[i][j] = 0;
                    else return memo[i][j] = dfs(greatThan[i], j^1);
                }
            };
            ans += dfs(k, 1);
        }
        
        return ans;
    }

    int oddEvenJumps2(vector<int>& arr) {
        // 自行解答
        int n = arr.size();

        // 从右到左遍历 arr，严格递增，相同的值取最小下标
        vector<pair<int, int>> suffix; suffix.emplace_back(arr[n-1], n-1);
        // 数据和作用详见下文注释
        vector<int> lessThan(n, n), greatThan(n, n); 
        
        int ans = 1;
        vector dp(n+1, vector<int>(2, -1));
        dp[n][0] = 0, dp[n][1] = 0;
        dp[n-1][0] = 1, dp[n-1][1] = 1;
        for (int k=n-2; k>=0; --k) {
            // 从后遍历，计算 arr[k] 小于等于后缀中最小的值
            auto it = ranges::lower_bound(suffix, arr[k], {}, &pair<int, int>::first);
            if (it != suffix.end())
                lessThan[k] = it->second;

            // 计算 arr[k] 大于等于后缀中的最大的值
            if (it != suffix.end() && it->first == arr[k])
                greatThan[k] = it->second;
            else if (it != suffix.begin()) {greatThan[k] = (--it)->second; ++it;}
            // 将当前元素更新或插入后缀中
            if (it != suffix.end() && it->first == arr[k]) it->second = k;
            else suffix.insert(it, {arr[k], k});

            dp[k][1] = dp[lessThan[k]][0];
            dp[k][0] = dp[greatThan[k]][1];
            ans += dp[k][1];
        }
        
        return ans;
    }

};
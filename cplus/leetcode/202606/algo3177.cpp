#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // 按值进行转移
        unordered_map<int, vector<int>> dp;
        vector<int> mx(k+1);

        for (auto v: nums) {
            if (!dp.count(v)) dp[v] = vector<int>(k+1);

            auto & pre = dp[v];
            for (int i=0; i<=k; i++) {
                pre[i] ++;                                  // 从相同值转移过来，初始化
                if (i) pre[i] = max(pre[i], mx[i-1] + 1);   // 从不同值的最大长度转移
            }
            // 更新最大值
            for (int i=0; i<=k; i++) {
                mx[i] = max(mx[i], pre[i]);
            }
        }

        return mx[k];
    }
};
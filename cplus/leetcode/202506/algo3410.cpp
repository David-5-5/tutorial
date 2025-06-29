#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
// 题解有三种方法：包括线段树，前后缀分解以及前缀和
// 其中线段树的思路想到了，但是觉得太复杂了。
// 看过的数据结构书介绍最大子数组和，有二分递归方法
// 递：分别求出前后两端的和，最大值，前缀及后缀等，详情记不清楚了
// 归：合并求出整段的和，最大值，前缀及后缀
// 这种递归的思路可以用于线段树
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        // 参考题解 - 前缀和 + 枚举右维护左
        long long ans = INT_MIN, s= 0, all_min = 0, no_del_min = 0;
        unordered_map<int, long long> del_min_s;
        for (auto x : nums) {
            s += x;
            ans = max(ans, s - all_min);
            if (x < 0) {
                del_min_s[x] = min(del_min_s[x], no_del_min) + x;
                all_min = min(all_min, del_min_s[x]);
                no_del_min = min(no_del_min, s);
            }
        }
        return ans;
    }
};
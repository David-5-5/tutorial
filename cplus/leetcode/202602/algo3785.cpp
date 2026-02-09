#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        // 自行解答，结合：
        // - 问题1，判断是否可以重新排序，合并统计两个数组出现次数 m <= n
        // - 问题2，计算 nums[i] forbidden[i] 相等需要移动的数量 max((n+1)/2, m)
        // 注：上下两个问题的 n m 不同
        int n = nums.size(), m = 0;
        unordered_map<int, int> cnt;
        for (int i=0; i<n; i++) {
            cnt[nums[i]] ++; cnt[forbidden[i]] ++;
            m = max(m, cnt[nums[i]]); m = max(m, cnt[forbidden[i]]);
        }
        if (m > n) return -1;

        m = 0; n = 0; cnt.clear();
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == forbidden[i]) {
                n ++; cnt[nums[i]] ++;
                m = max(m, cnt[nums[i]]);
            }
        }
        return max((n+1)/2, m);

    }
};
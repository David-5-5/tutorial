#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    long long findScore(vector<int>& nums) {
        // 自行解答，关键 stable_sort 要用稳定排序
        long long ans = 0;
        unordered_set<int> marked;
        int n = nums.size(), ids[n];
        iota(ids, ids+n, 0);
        stable_sort(ids, ids+n, [&](int i, int j){   // 稳定排序
            return nums[i] < nums[j];
        });         

        for (int i=0; i<n; i++) { 
            int inx = ids[i];
            if (marked.count(inx)) continue;
            ans += nums[inx];
            marked.insert(inx+1), marked.insert(inx), marked.insert(inx-1);
        }
        return ans;
    }

    long long findScore2(vector<int>& nums) {
        // 分组循环，按递减分段，每段最小值一定可以入选，然后倒着间隔 1 枚举
        // 用自己的分组循环模板，比题解的分组循环写更容易理解
        long long ans = 0;
        int i = 0, n = nums.size();
        while (i < n) {
            int st = i ++;
            while (i < n && nums[i-1]>nums[i]) i++;
            for (int j=i-1; j>=st; j-=2) ans += nums[j];
            i++; // i-1 选择 i 不选
        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        // 自行解答 - 两两相加 -> 两数之和为 0
        unordered_map<int, int> cnt;
        
        for (auto& v1 : nums1) {
            for (auto& v2 : nums2) {
                cnt[v1+v2] ++;
            }
        }

        int ans = 0;
        for (auto& v1 : nums3) {
            for (auto& v2 : nums4) {
                ans += cnt[-(v1+v2)];
            }
        }
        return ans;
    }
};
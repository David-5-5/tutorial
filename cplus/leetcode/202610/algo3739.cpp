#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        // 将前缀和排序
        vector<int> s_pres = {0}; int pres = 0; long long ans = 0;
        
        for (auto & v: nums) {
            // 等于target 为 1， 不等于 target 为 -1
            if (v == target) pres ++;
            else pres --;
            // auto it = upper_bound(s_pres.begin(), s_pres.end(), pres-1);
            // 查找小于当前前缀和 pres 的数量，表明子数组中 target 的数量严格大于数组的一半
            auto it = lower_bound(s_pres.begin(), s_pres.end(), pres);
            ans += it - s_pres.begin();
            s_pres.insert(it, pres);
        }

        return ans;        
    }

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        // 有序数组中查找比较慢，是否计数方法提升效率      
    }    
};
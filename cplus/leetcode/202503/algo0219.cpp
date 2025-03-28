#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size(), id[n];
        iota(id, id+n, 0);
        sort(id, id+n, [&](int i, int j){
            return nums[i] < nums[j];
        });

        for (int i=0; i<n-1; i++) {
            if (nums[id[i]] == nums[id[i+1]] && id[i+1] - id[i] <= k) {
                return true;
            }
        }
        return false;
    }
};
#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        auto min_v = ranges::min(nums1);
        if (min_v % 2) return true;
        for (auto& v : nums1) if (v % 2) return false;

        return true;
    }
};
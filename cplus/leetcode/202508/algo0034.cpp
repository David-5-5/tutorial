#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // vector<int> searchRange(vector<int>& nums, int target) {
    //     auto left = ranges::lower_bound(nums, target);
    //     if (left == nums.end() || *left != target) return {-1,-1};
    //     int l = left - nums.begin();
    //     int right = ranges::lower_bound(nums, target+1)-nums.begin()-1;
    //     return {l, right};
    // }
    vector<int> searchRange(vector<int>& nums, int target) {
        auto left = ranges::lower_bound(nums, target);
        if (left == nums.end() || *left != target) return {-1,-1};
        // left - nums.begin() 返回的是 difference_type 类型（通常是 long）
        // 直接放入 int 类型的向量中，这在列表初始化时是不允许的。
        // 添加 static_cast<int>() 消除窄化转换的错误提示
        return {static_cast<int>(left - nums.begin()), 
           static_cast<int>(ranges::lower_bound(nums, target+1)-nums.begin()-1)};
    }
};
#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 爬楼梯
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        // 不能用背包，背包组合数不计算顺序
        // 普通爬楼梯 1、2 步
        // 本题相当于可用 nums 中方式爬上 target 高的楼梯
        vector<unsigned> f(target+1); // int 会溢出
        f[0] = 1;
        for (int i=1; i<=target; i++) 
            for (auto& v:nums) 
                if (i >= v) 
                    f[i] += f[i-v];
        return f[target];
    }
};

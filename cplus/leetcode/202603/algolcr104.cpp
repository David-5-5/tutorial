#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 同 377
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned> f(target+1); // int 会溢出
        f[0] = 1;
        for (int i=1; i<=target; i++) 
            for (auto& v:nums) 
                if (i >= v) 
                    f[i] += f[i-v];
        return f[target];
    }
};

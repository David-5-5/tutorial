#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 进阶
class Solution {
public:
    int countSpecialSubsequences(vector<int>& nums) {
        // 参考题解
        const int mod = 1e9 + 7;

        // f0 表示正整数个 0 组成的子序列
        // f1 表示正整数个 0 紧接着正整数个 1 组成的子序列
        // f2 表示正整数个 0 紧接着正整数个 1，最后正整数个 2 组成的子序列
        // 状态转移时
        // 当 nums[i] == 0 时，
        int f0 = 0, f1 = 0, f2 = 0;
        for (auto x:nums) {
            if (x == 0) f0 = ((long)f0 * 2 + 1) % mod;
            if (x == 1) f1 = ((long)f1 * 2 + f0) % mod;
            if (x == 2) f2 = ((long)f2 * 2 + f1) % mod;
        }
        
        return f2;
    }
};
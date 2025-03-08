#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 进阶
class Solution {
public:
    int countSpecialSubsequences(vector<int>& nums) {
        
        const int mod = 1e9 + 7;

        int f0 = 0, f1 = 0, f2 = 0;
        for (auto x:nums) {
            if (x == 0) f0 = ((long)f0 * 2 + 1) % mod;
            if (x == 1) f1 = ((long)f1 * 2 + f0) % mod;
            if (x == 2) f2 = ((long)f2 * 2 + f1) % mod;
        }
        
        return f2;
    }
};
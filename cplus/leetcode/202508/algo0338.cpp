#include <bits/stdc++.h>
using namespace std;

// 位运算 - 基础题
class Solution {
public:
    vector<int> countBits(int n) {
        // 动态规划 时间复杂度：O(n) - 最高位
        vector<int> ans(n+1);
        int highBit = 0;
        for (int i = 1; i <= n; ++i) {
            if ((i & (i-1)) == 0) {
                highBit = i;
            }
            ans[i] = ans[i-highBit] + 1;
        }
        return ans;     
    }
};
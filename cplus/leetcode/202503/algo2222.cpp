#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    long long numberOfWays(string s) {
        // 参考题解 数学方法
        int n = s.size();
        int c1 = count(s.begin(), s.end(), '1');   // s 中 '1' 的个数
        long res = 0;
        int cnt1 = 0; // 当前 1 的数量

        for(int i=0; i<n; i++) {
            if (s[i] == '1') cnt1 ++;
            if (s[i] == '1') res += (i+1-cnt1) * (n-c1-(i+1-cnt1));
            else res += cnt1 * (c1-cnt1);
        }
        return res;
        
    }
};
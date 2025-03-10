#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 一维 DP
class Solution {
public:
    int minimumTime(string s) {
        // 参考题解
        // 启示：
        // 前后端操作 - 前后缀分解
        // 根据状态转移方程递推 代替 记忆化搜索，这样易于进行优化和组合
        int n = s.size();
        
        vector<int> suf(n+1);
        for (int i=n-1; i>=0; i--) {
            if (s[i] == '0')
                suf[i] = suf[i+1];
            else suf[i] = min(suf[i+1] + 2, n-i);
        }
    
        int ans = suf[0], pre = 0;
        for (int i=0; i<n-1; i++) {
            if (s[i] == '1')
                pre = min(pre+2, i+1);
            ans = min(ans, pre+suf[i+1]);
        }
        
        return ans;      
    
    }


};
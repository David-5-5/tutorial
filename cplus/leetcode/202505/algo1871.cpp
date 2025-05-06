#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        // 自行解答
        int n = s.length();
        vector<int> dp(n);          // 默认为 0：不可达到
        vector<int> pres(n+1, 1);   // dp 前缀和 dp[0] = 1 除pres[0] 外其他默认为 1 
        dp[0] = 1, pres[0] = 0;     // 初始化
        for (int j=minJump; j<n; ++j) {     // 从 minJump开始遍历
            // pres[j-minJump+1]-pres[max(0, j-maxJump)] > 0  
            // 表示 j-maxJump ~ j-minJump 之间存在可达到点 
            // 可到达点为 1， 不可到达为 0 这样用前缀和 O(1)时间完成检查
            if (s[j] == '0' && pres[j-minJump+1]-pres[max(0, j-maxJump)]){
                dp[j] = 1;
            }
            pres[j+1] = (pres[j] + dp[j]);
        }

        return dp[n-1];    
    }
};
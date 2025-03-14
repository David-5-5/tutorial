#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        // 自行解答
        sort(words.begin(), words.end(), [](string a, string b) {return a.size()<b.size();});

        int n = words.size();
        unordered_map<string, int> indices; // 记录 word 下标
        for (int i=0; i<n; i++) {
            indices[words[i]] = i;
        }

        // 转移方程： f[i] = max(f[j]) + 1， word[j] 是 word[i] 的前身
        int ans = 0;
        vector<int> dp(n);          
        for (int i=0; i<n; i++) {
            string w = words[i];
            for (int j=0; j<w.size(); j++) {
                // del j from w 遍历 words[i] 前身
                string slice = w.substr(0,j)+w.substr(j+1);
                if (indices.count(slice)) { // 查找 words[i] 的前身
                    dp[i] = max(dp[i], dp[indices[slice]]);
                }
            }
            dp[i] ++;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
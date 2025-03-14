#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        // 自行解答
        sort(words.begin(), words.end(), [](string a, string b) {return a.size()<b.size();});

        int n = words.size();
        unordered_map<string, int> indices; 
        for (int i=0; i<n; i++) {
            indices[words[i]] = i;
        }
        int ans = 0;
        vector<int> dp(n);
        for (int i=0; i<n; i++) {
            string w = words[i];
            for (int j=0; j<w.size(); j++) {
                // del j from w
                string slice = w.substr(0,j)+w.substr(j+1);
                if (indices.count(slice)) {
                    dp[i] = max(dp[i], dp[indices[slice]]);
                }
            }
            dp[i] ++;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
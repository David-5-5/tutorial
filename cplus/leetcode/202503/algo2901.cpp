#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 一维 DP
class Solution {
public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        auto check = [&](int i, int j) -> bool {
            if (words[i].size() != words[j].size() || groups[i] == groups[j]) return false;
            int cnt = 0;
            for (int k=0; k<words[i].size(); k++) {
                if (words[i][k] == words[j][k]) cnt ++;
            }
            return (words[i].size() == cnt + 1);
        };

        int n = words.size(), begin = n - 1;
        vector<int> f(n), from(n);
        for (int i = n-1; i>=0; i--) {
            for (int j=i+1; j<n; j++) {
                if (f[j] > f[i] && check(i, j)){
                    f[i] = f[j];
                    from[i] = j;
                }
            }
            f[i] ++;    // 计数自身
            if (f[i] > f[begin]) {
                begin = i;
            }
        }
        int m = f[begin];   // 最大路径，begin为起点
        vector<string> ans(m);
        for (int i = 0; i < m; i++) {
            ans[i] = words[begin];
            begin = from[begin];    // 下一个
        }
        return ans;
    
    }
};
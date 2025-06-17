#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int numSplits(string s) {
        // 自行解答
        int n = s.length(), ans = 0;
        vector<int> suf_cnt(n);
        set<char> chset;
        for (int i=n-1; i; i--) {
            chset.insert(s[i]);
            suf_cnt[i] = chset.size();
        }

        chset.clear();
        for (int i=0; i<n-1; ++i) {
            chset.insert(s[i]);
            if (chset.size() == suf_cnt[i+1]) ans++;
        }
        return ans;        
    }
};
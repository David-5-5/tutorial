#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        // 自行解答
        int n = s.length();
        vector<pair<int, int>> suf_cnt(n, {0,0});
        for (int i=n-1; i; --i) {
            if (i<n-1) suf_cnt[i] = suf_cnt[i+1];
            if (s[i] == '0') suf_cnt[i].first += 1;
            else suf_cnt[i].second += 1;
        }
        int zero_cnt=0, one_cnt=0;
        int ans = n;
        for (int i=0; i<n-1; ++i) {
            if (s[i] == '0') zero_cnt += 1;
            else one_cnt += 1;
            
            ans = min(ans, min(one_cnt + suf_cnt[i+1].first,  // 前缀全 0 ，后缀全 1
                    min(one_cnt + suf_cnt[i+1].second, zero_cnt + suf_cnt[i+1].first))); // 全 0 或 全 1     

        }
        return ans;        
    }
};
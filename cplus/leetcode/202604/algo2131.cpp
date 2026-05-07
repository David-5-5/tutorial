#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int ans = 0; bool mid = false;
        
        unordered_map<string, int> cnt;
        for (auto w: words) cnt[w] ++;

        for (auto &[w, c]: cnt) {
            if (c == 0) continue;
            if (w[0] == w[1]) {
                ans += (c / 2) * 4;
                c -= (c / 2) * 2;
                if (c && !mid) { ans +=2; mid = true;}
            } else {
                string rev = string(1, w[1]) + w[0];
                
                if (cnt.count(rev)) {
                    auto sub = min(cnt[rev], c);
                    ans += sub * 4; cnt[rev] -= sub; c -= sub;
                }
                // 错误写法
                // if (cnt.count(rev)) {
                //     ans += min(cnt[rev], cnt[w]) * 4;
                //     cnt[rev] -= min(cnt[rev], cnt[w]);   // 
                //     cnt[w] -= min(cnt[rev], cnt[w]);     // min 结果不一致
                // }                
            }
        } 

        return ans;        
    }    
};


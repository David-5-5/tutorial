#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.3 曼哈顿距离
class Solution {
public:
    int maxDistance(string s, int k) {
        // 自行解答
        int ans = 0;
        vector<int> cnt(4) ;
        for (auto& ch : s) {
            if (ch == 'N') cnt[0] ++;
            else if (ch == 'S') cnt[1] ++;
            else if (ch == 'E') cnt[2] ++;
            else cnt[3] ++;
            
            int mx = max(cnt[0],cnt[1]) + max(cnt[2],cnt[3]),
                mn = min(cnt[0],cnt[1]) + min(cnt[2],cnt[3]);
            ans = max(ans, mx - mn + min(2 * k, 2 * mn));
        }
        return ans;
    }
};
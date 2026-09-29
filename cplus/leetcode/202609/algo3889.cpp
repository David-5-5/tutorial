#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mirrorFrequency(string s) {
        vector<int> l_cnt(26), d_cnt(10);

        for (auto& ch : s) {
            if (ch >= '0' && ch <= '9') {
                d_cnt[ch-'0'] ++;
            } else l_cnt[ch-'a'] ++;
        }

        int ans = 0;
        for (int i=0; i<13; i++) {
            ans += abs(l_cnt[i] - l_cnt[25-i]);
        }
        for (int i=0; i<5; i++) {
            ans += abs(d_cnt[i] - d_cnt[9-i]);
        }
        return ans;
    }
};
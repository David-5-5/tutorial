#include <bits/stdc++.h>
using namespace std;

// 顺序
class Solution {
public:
    int minimumLength(string s) {
        vector<int> cnt(26);
        for (auto& ch : s) cnt[ch-'a'] ++;

        int ans = 0;
        for (auto c: cnt) {
            if (c == 0) continue;
            if (c%2) ans ++;
            else ans += 2;
        }
        return ans;
    }
};
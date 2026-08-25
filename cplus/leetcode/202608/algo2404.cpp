#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int partitionString(string s) {
        int ans = 0; vector<int> cnt(26);
        for (auto ch: s) {
            if (cnt[ch - 'a']) {
                ans ++; fill(cnt.begin(), cnt.end(), 0);
            }
            cnt[ch - 'a'] ++;
        }
        return ans + 1;
    }
};
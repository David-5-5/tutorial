#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> cnt1(26), cnt2(26);
        for (int i=0; i<s.length(); i++) {
            cnt1[s[i]-'a'] ++; cnt2[t[i]-'a'] ++;
        }

        int ans = 0;
        for (int i=0; i<26; i++) ans += abs(cnt1[i] - cnt2[i]);

        return ans / 2;
    }
};
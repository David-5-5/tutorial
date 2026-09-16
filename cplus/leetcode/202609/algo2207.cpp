#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        long long ans = 0; int n = text.length(), p0_cnt = 0, p1_cnt = 0;
        vector<int> suf_p1(n);

        for (int i=n-1; i>=0; i--) {
            if (text[i] == pattern[1]) p1_cnt ++;
            else if (text[i] == pattern[0]) p0_cnt ++;

            suf_p1[i] = p1_cnt;
        }

        for (int i=0; i<n-1; i++) {
            if (text[i] == pattern[0]) {
                ans += suf_p1[i+1];
            }
        }
        return ans + max(p0_cnt, p1_cnt);
    }
};
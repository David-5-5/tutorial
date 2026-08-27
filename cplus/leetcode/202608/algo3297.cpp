#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        if (m < n) return 0;
        vector<int> cnt1(26), cnt2(26);

        for (int i=0; i<n; i++) {
            cnt1[word1[i] - 'a'] ++;
            cnt2[word2[i] - 'a'] ++;
        }
        cnt1[word1[n-1] - 'a'] --;
        
        int l = 0;
        long long ans = 0;
        for (int r=n-1; r<m; r++) {
            auto check = [&]() -> bool {
                for (int i=0; i<26; i++) {
                    if (cnt1[i] < cnt2[i]) return false;
                }
                return true;
            };
            cnt1[word1[r]-'a'] ++;
            while (cnt1[word1[l]-'a'] > cnt2[word1[l]-'a']) {
                cnt1[word1[l]-'a'] --; l ++;
            }
            if (check()) ans += l + 1;
        }
        return ans;
        
    }
};
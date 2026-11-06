#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> cnt(26);
        for (auto &ch : word) cnt[ch-'a'] ++;

        int ans = word.length();
        for (int i=0; i<26; i++) {
            if (cnt[i] == 0) continue;
            int res = 0;
            for (int j=0; j<26; j++) {
                if (i == j || cnt[j] == 0) continue;
                if (cnt[j] >= cnt[i]) res += max(0, cnt[j] - cnt[i] - k);
                else res += cnt[j];
            }

            ans = min(ans, res);
        }
        return ans;
    }
};
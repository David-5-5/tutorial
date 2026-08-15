#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> mx_cnt(26);
        
        for (auto & word : words2) {
            vector<int> cnt(26);
            for (auto & ch: word) cnt[ch-'a'] ++;

            for (int i=0; i<26; i++) mx_cnt[i] = max(mx_cnt[i], cnt[i]);
        }

        vector<string> ans;
        for (auto & word: words1) {
            vector<int> cnt(26);
            for (auto & ch: word) cnt[ch-'a'] ++;

            bool satified = true;
            for (int i=0; i<26; i++) if (mx_cnt[i] > cnt[i]) {
                satified = false; break;
            }

            if (satified) ans.push_back(word);
        }

        return ans;
    }
};
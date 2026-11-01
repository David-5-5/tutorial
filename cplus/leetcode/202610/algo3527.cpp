#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findCommonResponse(vector<vector<string>>& responses) {
        unordered_map<string, int> cnt;
        
        for (auto & rep: responses) {
            sort(rep.begin(), rep.end());
            rep.erase(unique(rep.begin(), rep.end()), rep.end());
            for (auto & word : rep) cnt[word] ++;
        }

        string ans; int mx_c = 0;

        for (auto &[word, c]: cnt) {
            if (mx_c < c) {
                ans = word; mx_c = c;
            } else if (mx_c == c) ans = min(ans, word);
        }
        return ans;
    }
};
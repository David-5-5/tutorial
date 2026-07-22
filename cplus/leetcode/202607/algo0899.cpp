#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        // 自行解答，观察规律
        if (k > 1) {
            sort(s.begin(), s.end()); return s;
        }

        vector<int> idx[26];
        for (int i=0; i<s.length(); i++) idx[s[i]-'a'].push_back(i);
        string ans = s;
        for (int i=0; i<26; i++) {
            if (idx[i].size()) {
                for (int pos : idx[i]) {
                    auto cur = s.substr(pos) + s.substr(0, pos);
                    ans = min(ans, cur);
                }
                break;
            }
        }
        
        return ans;
    }
};
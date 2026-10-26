#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getSmallestString(string s, int k) {
        string ans;
        for (auto& ch: s) {
            if (k == 0) {
                ans.push_back(ch);
                continue;
            }
            for (auto i=0; i<26; i++) {
                auto dis = abs(ch-'a'-i);
                if (min(dis, 26-dis) <= k) {
                    ans.push_back('a'+i);
                    k -= min(dis, 26-dis);
                    break;
                }
            }
        }
        return ans;
    }
};
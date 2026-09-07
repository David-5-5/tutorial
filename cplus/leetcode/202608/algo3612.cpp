#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string processStr(string s) {
        string ans;

        for (auto c: s) {
            if (c>='a' && c<='z') ans.push_back(c);
            else if (c == '*') {
                if (ans.length()) ans.pop_back();
            } else if (c == '#') ans += ans;
            else reverse(ans.begin(), ans.end());
        }

        return ans;
    }
};
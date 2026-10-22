#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> kvals;
        for (auto & k: knowledge) {
            kvals[k[0]] = k[1];
        }

        string ans, key; bool in_key = false;
        for (auto & ch : s) {
            if (ch == '(') {
                in_key = true;
            } else if (ch == ')') {
                if (kvals.count(key)) ans += kvals[key];
                else ans.push_back('?');
                key.clear(); in_key = false;
            } else {
                if (in_key) key.push_back(ch);
                else ans.push_back(ch);
            }
        }
        return ans;
    }
};
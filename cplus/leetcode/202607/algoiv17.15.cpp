#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
                sort(words.begin(), words.end(), [](const string& a, const string& b) {
            if (a.length() == b.length()) return a < b;
            return a.length() < b.length();
        });

        unordered_set<string> hash_word; unordered_set<int> hash_len;
        string ans = "";
        for (auto w: words) {
            auto check = [&](this auto&& check, string suf, bool isSuf) -> bool {
                if (isSuf && hash_word.count(suf)) return true;

                for (auto l: hash_len) {
                    if (l < suf.length() && hash_word.count(suf.substr(0, l)) &&
                        check(suf.substr(l), true)) return true;
                }
                return false;
            };
            if (check(w, false) && w.length() > ans.length()) ans = w;
            hash_word.insert(w); hash_len.insert(w.length());
        }
        return ans;

    }
};
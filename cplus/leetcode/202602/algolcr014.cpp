#include <bits/stdc++.h>
using namespace std;

// 同 567
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        vector<int> target(26), cur(26);
        for (auto ch: s1) target[ch-'a']++;

        for (int i=0; i<s1.length()-1; i++) cur[s2[i]-'a'] ++;
        for (int i=s1.length()-1; i<s2.length(); ++i) {
            cur[s2[i]-'a'] ++;
            auto check = [&]() {
                for (int j=0; j<26; ++j) {
                    if (target[j] != cur[j]) return false;
                }
                return true;
            };
            if (check()) return true;
            cur[s2[i-s1.length()+1]-'a'] --;
        }
        return false;        
    }
};
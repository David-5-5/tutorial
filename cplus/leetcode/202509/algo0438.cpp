#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // 自行解答
        vector<int> ans;
        if (s.length() < p.length()) return ans;
        vector<int> target(26), cur(26);
        for (auto ch: p) target[ch-'a']++;

        for (int i=0; i<p.length()-1; i++) cur[s[i]-'a'] ++;
        for (int i=p.length()-1; i<s.length(); ++i) {
            cur[s[i]-'a'] ++;
            auto check = [&]() {
                for (int j=0; j<26; ++j) {
                    if (target[j] != cur[j]) return false;
                }
                return true;
            };
            if (check()) ans.push_back(i-p.length()+1);
            cur[s[i-p.length()+1]-'a'] --;
        }
        return ans;     
    }
};
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> split(string s) {
        vector<string> ans;
        int n = s.length(), start = 0, diff = 0, i = 0;
        while (i < n) {
            if (s[i] == '1') diff ++;
            else diff --;
            if (diff == 0 && i > start) {
                ans.push_back(s.substr(start, i-start+1));
                start = i + 1;
            }
            i++;
        }
        return ans;
    }

    string makeLargestSpecial(string s) {
        if (s.length() <= 4) return s;
        auto subs = split(s);
        // 分割字符串，递归排序
        if (subs.size() == 1) {
            int n = subs[0].length();
            // subs[0].substr(0, 1) + makeLargestSpecial(subs[0].substr(1, n-2)) + subs[0].substr(n-1, 1);
            return "1" + makeLargestSpecial(subs[0].substr(1, n-2)) + "0";
        } 
        vector<string> res;
        // 每个特殊子串求其最大字典序
        for (auto sub: subs) res.emplace_back(makeLargestSpecial(sub));

        // 排序后合特殊子串
        sort(res.rbegin(), res.rend());
        string ans = "";
        for (auto sub: res) ans += sub;
        return ans;
    }
};
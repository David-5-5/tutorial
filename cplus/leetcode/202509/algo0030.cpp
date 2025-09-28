#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // 参考题解 - 看懂了，明天再做
        vector<int> ans;
        int p = words[0].length(), q = words.size();
        if (s.length() < p * q) return ans;
        unordered_map<string, int> cnt;
        for (auto w: words) cnt[w] ++;

        for (int i=0; i<s.length() - p * q; ++i) {
            auto check = [&]() {
                unordered_map<string, int> cur;
                for (int j=0; j<q; ++j) {
                    auto word = s.substr(i+j*p, p);
                    if (cnt.count(word)) {
                        cur[word] ++;
                        if (cur[word] > cnt[word]) return false;
                    } else return false;
                }
                return true;
            };
            if (check()) ans.push_back(i);
        }
        return ans;
    }
};
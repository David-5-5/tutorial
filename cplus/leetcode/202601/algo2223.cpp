#include <bits/stdc++.h>
using namespace std;

// 字符串 - 二、Z 函数（后缀的前缀）
class Solution {
public:
    long long sumScores(string s) {
        // 2026.1.3 专题复习 - Z 函数
        // z 函数 模板
        auto zFunc = [&](string text) -> vector<int>{
            int t_len = (int)text.length();
            vector<int> ans(t_len);
            for (int i = 1, l = 0, r = 0; i < t_len; ++i) {
                if (i <= r && ans[i - l] < r - i + 1) {
                    ans[i] = ans[i - l];
                } else {
                    ans[i] = max(0, r - i + 1);
                    while (i + ans[i] < t_len && text[ans[i]] == text[i + ans[i]]) ++ans[i];
                }
                if (i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
            }
            return ans;
        };
        // z函数 模板

        vector<int> z_res = zFunc(s);
        return reduce(z_res.begin(), z_res.end(), 0LL) + s.length();   
    }
};
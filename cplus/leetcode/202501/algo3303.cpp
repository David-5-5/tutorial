#include <bits/stdc++.h>
using namespace std;

// 双周赛 140
class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        int n = s.size(), m = pattern.size();

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

        vector<int> pre_z = zFunc(pattern + s);
        reverse(pattern.begin(), pattern.end()), reverse(s.begin(),s.end());
        vector<int> suf_z = zFunc(pattern + s);

        // for (auto v : pre_z) cout << v;
        // cout << endl;

        for (int i=m; i<=n; i++) { // i = n 时 后续长度为最后 m 个字符
            if (pre_z[i] + suf_z[n+m-i] >= m - 1)
                return i - m;
        }
        return -1;
        
    }
};
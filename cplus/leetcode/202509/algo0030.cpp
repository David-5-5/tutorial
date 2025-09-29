#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // 参考题解 - 看懂了，明天再做
        vector<int> ans;
        int m = words[0].length(), n = words.size(), ln = s.length();
        if (ln < m * n) return ans;
        unordered_map<string, int> cnt;
        for (auto w: words) cnt[w] ++;

        for (int i=0; i<m; ++i) {
            unordered_map<string, int> cur;
            auto check = [&] () -> bool {
                for (auto [k, v]:cnt) {
                    if (cur[k] != v) return false;
                }
                return true;
            };

            for (int j=i; j+m<=ln && j<(n-1)*m; j+=m) cur[s.substr(j, m)]++;
            for (int j=i+(n-1)*m; j+m<=ln; j+=m) {
                cur[s.substr(j, m)] ++;
                if (check()) ans.push_back(j-(n-1)*m);
                cur[s.substr(j-(n-1)*m, m)] --;
            }
        }
        return ans;
    }
};
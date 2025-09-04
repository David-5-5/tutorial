#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.3 划分型回溯
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        // 自行解答
        vector<string> ans; int n = s.length();

        auto to_ip = [](vector<int>& seg) -> string {
            string res = to_string(seg[0]);
            for (int i=1; i<4; ++i) res += "." + to_string(seg[i]);
            return res;
        };

        auto dfs = [&](this auto&& dfs, int i, vector<int>& seg) -> void {
            if (i == n) {
                if (seg.size() == 4) ans.push_back(to_ip(seg));
                return;
            }
            
            int cur = 0;
            for (int j=i; j<min(i+3,n); ++j) {
                cur = cur * 10 + (s[j] - '0');
                if (cur < 256) {
                    seg.push_back(cur);
                    dfs(j+1, seg);
                    seg.pop_back();
                }
                if (cur == 0) break;
            }
        };
        vector<int> seg; dfs(0, seg);
        return ans;
    }
};
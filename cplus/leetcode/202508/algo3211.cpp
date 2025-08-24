#include <bits/stdc++.h>
using namespace std;

// 位运算 - 基础题
class Solution {
public:
    vector<string> validStrings(int n) {
        // 自行解答，广度优先搜索
        vector<string> ans; ans.push_back("1"); ans.push_back("0");
        while (ans[0].length() < n) {
            vector<string> nxt;
            for (auto &s : ans) {
                nxt.push_back(s + "1");
                if (s.back() == '1') 
                    nxt.push_back(s + "0");
            }
            ans = move(nxt);
        }
        return ans;
    }

    vector<string> validStrings2(int n) {
        vector<string> ans;
        int mask = (1 << n) - 1;
        for (int x=0; x<(1<<n) ; ++x) {
            if (((x>>1) & x ) == 0) {
                ans.push_back(bitset<18>(x^mask).to_string().substr(18-n));
            }
        }
        return ans;
    }

    vector<string> validStrings3(int n) {
        // 回溯，深度优先搜索
        vector<string> ans;
        string path(n, '0');
        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }
            path[i] = '1';
            dfs(i+1);
            path[i] = '0';  // 恢复现场
            if (i == 0 || path[i-1] == '1') dfs(i+1);
        };
        dfs(0);
        return ans;
    }
};
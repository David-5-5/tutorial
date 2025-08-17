#include <bits/stdc++.h>
using namespace std;

// 二叉树 - 2.16 其他
class Solution {
public:
    int countHighestScoreNodes(vector<int>& parents) {
        // 自行解答
        long mx = 0;
        int cnt = 0;
        int n = parents.size();

        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) {
            g[parents[i]].push_back(i);
        }        

        auto dfs = [&](this auto&& dfs, int u) -> int {
            // 按题意模拟
            long score = 1;
            int rem = n-1;
            for (auto v: g[u]) {
                int v_cnt = dfs(v);
                if (v_cnt) score *= v_cnt;
                rem -= v_cnt;   // 根节点为 v 的子树数量
            }
            if (rem) score *= rem;

            if (score == mx) cnt ++;
            else if (score > mx) {cnt = 1; mx = score;}
            return n - rem; // 根节点为 u 的子树数量
        };
        dfs(0);
        return cnt;      
    }
};
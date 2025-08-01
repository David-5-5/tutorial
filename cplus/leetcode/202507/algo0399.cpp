#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.6 并查集 - 边权并查集
class UnionFind {
    vector<int> fa;
public:
    int cc;
    UnionFind(int n): fa(n), cc(n){
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; cc--;
        }
    }
};


class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 自行解答，AI辅助
        int cnt = 0; unordered_map<string, int> var_id;
        for (auto& e : equations) {
            for (int i = 0; i < 2; ++i) {
                if (!var_id.count(e[i])) {
                    var_id[e[i]] = cnt++;
                }
            }
        }
        vector<vector<double>> g(cnt, vector<double>(cnt, -1));
        for (int i = 0; i < equations.size(); ++i) {
            auto& e = equations[i]; double val = values[i];
            int u = var_id[e[0]], v = var_id[e[1]];
            g[u][v] = val; g[v][u] = 1 / val;
        }
        // 本来实现递归dfs + 记忆化搜索， AI直接给出 floyd 算法
        // 本题的图其实是一棵数，两个点之间不存在多条路径
        for (int k = 0; k < cnt; ++k) {
            for (int i = 0; i < cnt; ++i) {
                for (int j = 0; j < cnt; ++j) {
                    if (g[i][k] >= 0 && g[k][j] >= 0) {
                        g[i][j] = max(g[i][j], g[i][k] * g[k][j]);  // 用 max 初始值为-1
                    }
                }
            }
        }
        vector<double> ans;
        for (auto& q : queries) {
            if (!var_id.count(q[0]) || !var_id.count(q[1])) {
                ans.push_back(-1);
                continue;
            }
            int u = var_id[q[0]], v = var_id[q[1]];
            ans.push_back(g[u][v]);
        }
        return ans;   

    }
};
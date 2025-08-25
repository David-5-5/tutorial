#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.3 自底向上 DFS
class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        // 自行解答
        vector<int> ans(n);  vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        // 使用固定长度为 26 的 vector<int>  
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> vector<int> {
            vector<int> res(26);  res[labels[u]-'a'] = 1;
            for (auto &v : g[u]) {
                if (v == fa) continue;
                auto child = dfs(v, u);
                for (int i=0; i<26; ++i) res[i] += child[i];
            }
            ans[u] = res[labels[u]-'a']; 
            return res;
        };
        dfs(0, -1); return ans;
    }

    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        // 自行解答
        vector<int> ans(n);  vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        // 使用数组替换 vector<int> 
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> int * {
            int* res = new int[26];             // 堆上分配数组，函数结束后不释放
            memset(res, 0, 26*sizeof(int));     // 注意：memset第三个参数是字节数
            res[labels[u]-'a'] = 1;
            for (auto &v : g[u]) {
                if (v == fa) continue;
                auto* child = dfs(v, u);
                for (int i=0; i<26; ++i) res[i] += child[i];
                delete[] child;                 // 用完子节点的数组后及时释放，避免内存泄漏
            }
            ans[u] = res[labels[u]-'a']; 
            return res;
        };
        // 调用DFS并释放根节点返回的数组
        int* root = dfs(0, -1); delete[] root;
        return ans;
    }    
    
};

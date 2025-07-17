#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.4 字典树（trie）- 0-1 字典树（异或字典树）
struct Node {
    Node* son[2]{};
    int cnt = 0;
};

class Solution {
private:
    const int hi = 29;
    Node* root = new Node();
    void insert(int val) {
        auto node = root;
        node->cnt ++;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] == nullptr) node->son[v] = new Node();
            node = node->son[v];
            node->cnt ++;
        }
    }
    void del(int val) {
        auto node = root;
        node->cnt --;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v]->cnt == 1) {
                node->son[v] = nullptr;
                return;
            }
            node = node->son[v]; node->cnt --;
        }
    }

    int max_xor(int val) {
        int res = 0;
        auto node = root;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v^1] != nullptr) {
                res |= 1 << i; node = node->son[v^1];
            }else if (node->son[v] != nullptr)
                node = node->son[v];
            else return -1;
        }
        return res;
    }
public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        // 自行解答
        int n = parents.size(), root=0, m = queries.size();
        vector<vector<int>> g(n);
        for (int i=0; i<n; ++i)
            if (parents[i] == -1) root = i;
            else g[parents[i]].push_back(i);
        
        unordered_map<int, vector<pair<int,int>>> q;
        for (int i=0; i<m; ++i) {
            int u = queries[i][0], v = queries[i][1];
            q[u].emplace_back(i, v);
        }

        vector<int> ans(m);
        insert(root);
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            auto qs = q[u];
            for (auto& [i, v]: qs) {
                ans[i] = max_xor(v);
            }

            for (auto& v: g[u]) {
                if (v == fa) continue;
                insert(v);
                dfs(v, u);
                del(v);
            }

        };

        dfs(root, -1);
        return ans;
    }
};
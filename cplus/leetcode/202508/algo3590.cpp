#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


// 常用数据结构 - 8.5 动态开点线段树
class Solution {

public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        // 超时，也觉得没有必要
        unordered_map<int, vector<int>> tree; 
        // 动态开点线段树 - 模板 - 区间集合 - 单点更新
        auto update = [&] (this auto&& update, int l, int val, int start, int end, int p) -> void {
            if (l == start && l == end) {
                tree[p]={val}; return;
            }
            
            int m = start + ((end - start) >> 1);
            if (l <= m)
                update(l, val, start, m, p*2+1);
            else
                update(l, val, m + 1, end, p*2+2);
            if (tree[p].size() == 0) tree[p] = {val};
            else {
                auto it = ranges::lower_bound(tree[p], val);
                if (it == tree[p].end() || *it != val) tree[p].insert(it, val);
            }
        };

        auto query = [&] (this auto&& query, int l, int r, int start, int end, int p) -> vector<int> {
            
            if (!tree.count(p) || end < l || start > r) return {};
            if (l <= start && end <= r) {
                return tree[p];
            }

            int m = (start + end) >> 1;
            vector<int> left, right;
            if (l <= m) left = query(l, r, start, m, p*2+1);
            if (r > m) right = query(l, r, m+1, end, p*2+2);
            if (left.size() && right.size()) {
                vector<int> result; result.reserve(left.size() + right.size());
                merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result));
                auto last = std::unique(result.begin(), result.end()); result.erase(last, result.end());
                return result;
            } else if (left.size()) return left;
            else return right;
        };
        // 动态开点线段树 - 模板 
        int n = par.size();
        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) {
            g[par[i]].push_back(i);
        }
        vector<int> clock_in(n), clock_out(n);
        int clock = -1;
        auto dfs = [&](this auto&& dfs, int u, int fa, int x) -> void {
            clock_in[u] = ++clock;
            x = x ^ vals[u];
            update(clock_in[u], x, 0, n-1, 0);
            for (auto v: g[u]) {
                if (v == fa) continue;
                dfs(v, u, x);
            }
            clock_out[u] = clock;
        };
        dfs(0, -1, 0);

        int m = queries.size();
        unordered_map<int, vector<pair<int, int>>> qu;
        for (int i = 0; i<m; i++) {
            auto& u = queries[i][0], k = queries[i][1];
            qu[u].push_back({k, i});
        }
        vector<int> ans(m);
        for (auto& [u, k_arr]: qu) {
            auto res = query(clock_in[u], clock_out[u], 0, n-1, 0);
            for (auto& [k, i]:k_arr)
                if (res.size()<k) ans[i] = -1;
                else ans[i] = res[k-1];
        }

        return ans;        
    }

    vector<int> kthSmallest2(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        // 后续遍历树， std::set std::vector 超时
        int n = par.size();
        // 构建邻接表表示树
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i)  g[par[i]].push_back(i);
        
        vector<int> x_sum(n);
        // 深度优先搜索计算x_sum
        auto dfs = [&](this auto&& dfs, int u, int x) -> void {
            x_sum[u] = x ^ vals[u];
            for (int v : g[u]) dfs(v, x_sum[u]);
        };
        dfs(0, 0);
        
        int m = queries.size();
        // // 按节点分组存储查询
        unordered_map<int, vector<pair<int, int>>> qu;
        for (int i = 0; i < m; ++i) {
            int u = queries[i][0], k = queries[i][1];
            qu[u].emplace_back(k, i);
        }
        vector<int> ans(m);
  
        // 后序遍历处理每个节点的子树
        auto post = [&](this auto&& post, int u) -> set<int> {
            set<int> cur;  // 使用set维持有序性和去重
            cur.insert(x_sum[u]);
            
            for (int v : g[u]) {
                auto child = post(v);
                // 合并子节点的集合
                cur.insert(child.begin(), child.end());
            }
            
            // 处理当前节点的所有查询
            for (auto& [k, i] : qu[u]) {
                if (cur.size() < k) ans[i] = -1;
                else {
                    // 获取第k-1个元素（set是有序的）
                    auto it = cur.begin(); advance(it, k - 1); ans[i] = *it;
                }
            }
            return cur;
        };
        post(0);
        return ans;
    }    


};



int main() {
    vector<int> par = {-1,0,1}, vals = {5,2,7};
    vector<vector<int>> queries = {{0,1}, {1,2}, {1,3}, {2,1}};
    Solution().kthSmallest(par, vals, queries);
}
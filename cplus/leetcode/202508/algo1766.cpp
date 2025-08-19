#include <bits/stdc++.h>
using namespace std;

// 预处理 for 自行解答方案一
const int N = 50;
vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
set<int> factors[N+1];
int init = [] {
    factors[1].insert(1);
    for (int i=2; i<=50; ++i) {
        for (auto& p:primes)
            if (i % p == 0) factors[i].insert(p);
    }
    return 0;
}();


// 预处理 for 自行解答方案二
const int N = 51;
vector<int> coprimes[N];
int init = [] {
    for (int i=1; i<N; ++i) for (int j=1; j<N; ++j) {
        if (gcd(i, j) == 1) coprimes[i].push_back(j);
    }
    return 0;
}();


// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        // 自行解答 - 性能需要优化
        int n = nums.size(); vector<int> ans(n, -1);
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        
        // 每个递归使用 独立的path，影响性能，这个现场不好恢复
        // 恢复现场需要把删除的元素重新增加回来
        auto dfs = [&] (this auto&& dfs, int u, int fa, vector<int> path) -> void{
            for (int i = path.size()-1; i>=0; --i) {   // 查找与 u 互质的祖先节点
                if (gcd(nums[u], nums[path[i]]) == 1) {
                    ans[u] = path[i]; break;
                }
            }
            if (nums[u] == 1) path.clear();
            auto it=path.begin();
            while (it != path.end()) {  // 删除包含 u 对应质因子集合的祖先节点，保证 path 足够的小
                // 如果子节点和 u 不互质，则包含 u 对应质因子的祖先节点也与子节点不互质
                if (includes(factors[nums[*it]].begin(), factors[nums[*it]].end(),
                    factors[nums[u]].begin(), factors[nums[u]].end())) it = path.erase(it);
                else it++;
            }
            path.push_back(u);
            for (auto& v:g[u]) {
                if (v == fa) continue;
                dfs(v, u, path);
            }
        };

        dfs(0, -1, {}); return ans;
    }

    vector<int> getCoprimes2(vector<int>& nums, vector<vector<int>>& edges) {
        // 参考题解，相比较自行解答方案
        // 固定保持50个数值及其最后出现的位置，预处理每个值互质的集合
        int n = nums.size(); vector<int> ans(n, -1);
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        
        vector<pair<int, int>> path(51, {-1, -1});
        auto dfs = [&] (this auto&& dfs, int u, int fa, int depth, vector<pair<int, int>>& path) -> void{
            int mx_dep = -1;
            for (auto & p: coprimes[nums[u]]) {
                if (path[p].first > mx_dep) {
                    ans[u] = path[p].second; mx_dep = path[p].first;
                }
            }

            pair<int, int> tmp = path[nums[u]]; // 保存现场
            path[nums[u]] = {depth, u};
            for (auto& v:g[u]) {
                if (v == fa) continue;
                dfs(v, u, depth+1, path);
            }
            path[nums[u]] = tmp;         // 恢复现场
        };

        dfs(0, -1, 0, path); return ans;
    }
};
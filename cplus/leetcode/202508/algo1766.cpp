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

};
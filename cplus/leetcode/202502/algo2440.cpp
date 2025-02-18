#include <bits/stdc++.h>
using namespace std;

// 双周赛 89 复习
class Solution {
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        // 树上 DP
        // unordered_map<int, vector<int>> g;
        int n = nums.size();    // array of vector is better than unordered_map
        vector<int> g[n];

        for (auto& e:edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // 计算子树的大小，
        // 若子树大小为 target 删除边 形成目标值的连通块 返回 0
        // 若子树大小超过 target 则返回 -1, 无法创建价值相同连通块
        function<int(int,int,int)> dfs = [&] (int u, int fa, int target)->int {
        // The expression "auto dfs = [&](this auto&&, ...) is much fast than function<> dfs = [&](...)
        // auto dfs = [&] (this auto&& dfs, int u, int fa, int target) -> int{ 

            int value = nums[u]; // 节点 u 的价值

            for (int i=0; i<g[u].size(); i++) {
                if (g[u][i] == fa) continue;
                int res = dfs(g[u][i], u, target);
                if (res == -1) return res;
                else value += res;
            }

            if (value == target) return 0;
            else if (value > target) return -1;
            else return value;
        };
        
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int mx = ranges::max(nums);
        for (int i=min(sum, sum/mx); i; i--) {
            
            if (sum % i == 0) {
                if (dfs(0, -1, sum/i) == 0) return i - 1;
            }
        }
        return 0;
    }
};
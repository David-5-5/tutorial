#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.10 树上启发式合并
class Solution {
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        // 自行解答，通过二分查找找到缺失值。O(NlogN)
        // 题解 通过 O(1) 的时间找到缺失值，总体时间复杂度为 O(N)
        int n = parents.size();
        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) g[parents[i]].push_back(i);        

        vector<int> ans(n, 1);

        // 通过二分查找找到缺失值。
        auto find_loss = [] (const vector<int>& nums) {
            int l = 0, r = nums.size() + 1;  // 初始右边界为数组长度+1
            
            while (l + 1 < r) {
                int mid = (l + r) / 2;  // 计算中间位置    
                if (mid >= nums[mid - 1])  l = mid;  // 左侧满足条件，移动左边界
                else  r = mid;  // 右侧不满足条件，移动右边界
            }
            return r;  // r即为缺失的整数
        };
        // 
        
        auto post = [&](this auto&& post, int u) -> vector<int> {
            vector<int> cur;  // 使用 vector 通过 ranges::lower_bound 维持有序性和去重
            cur.push_back(nums[u]);
            
            for (int v : g[u]) {
                auto child = post(v);
                if (cur.size() < child.size()) swap(cur, child);
                for (int x : child) {
                    // ans[u] = max(ans[u], ans[v]);    // 取子树的最大缺失值
                    auto it = ranges::lower_bound(cur, x);
                    if (it == cur.end() || *it != x)
                        cur.insert(it, x);
                } 
            }

            ans[u] = find_loss(cur);   // 二分查找
            
            // 取消 上面语句 ans[u] = max(ans[u], ans[v]) 的注释
            // for (int i=ans[u]; i<=cur.size(); ++i) {
            //     if (cur[i-1] == i) ans[u] ++;
            //     else break;
            // }
            return cur;
        };
        post(0); return ans;
    }

    vector<int> smallestMissingValueSubtree2(vector<int>& parents, vector<int>& nums) {
        // 将上述 vector 改为 unordered_set, 递归子树最小缺失值的最大值，查找缺失值
        int n = parents.size();
        vector<vector<int>> g(n, vector<int>());
        for (int i=1; i<n; ++i) g[parents[i]].push_back(i);        

        vector<int> ans(n,1);
        
        auto post = [&](this auto&& post, int u) -> unordered_set<int> {
            unordered_set<int> cur;  //
            cur.push_back(nums[u]);
            
            for (int v : g[u]) {
                auto child = post(v);
                ans[u] = max(ans[u], ans[v]);
                if (cur.size() < child.size()) swap(cur, child);
                cur.merge(child);
            }
            while (cur.count(ans[u]) > 0) {
                ans[u]++;
            }
            return cur;
        };
        post(0); return ans;
    }    
};
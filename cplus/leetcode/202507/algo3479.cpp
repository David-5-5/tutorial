#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新）
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        // 自行解答 - 线段树 - 单点更新 - 最大值 - 二分查找
        int n = baskets.size();
        // 参考 oi-wiki 线段树模板 本题计算最大值 单点更新
        vector<int> tree(4 * n);   // 线段树空间
        auto update = [&] (this auto&& update, int l, int value, int s, int t, int p) -> void {
            if (l == s and l == t) {
                tree[p] = value;  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = s + ((t - s) >> 1);

            if (l <= m)
                update(l, value, s, m, p*2+1);
            else
                update(l, value, m + 1, t, p*2+2);
            tree[p] = max(tree[p*2+1], tree[p*2+2]);
        };

        auto query = [&] (this auto&& query, int val, int s, int t, int p) -> int {
            // [s, t] 为当前节点包含的区间, p为当前节点的编号
            if (tree[p] < val) return -1;
            if (s == t) return s;

            int m = s + ((t - s) >> 1);
            if (tree[p*2+1]>=val)
                return query(val, s, m, p * 2 + 1);
            else
                return query(val, m + 1, t, p * 2 + 2);
        };
        // 参考 oi-wiki 线段树模板 最常用的求和模板
        
        for (int i=0; i<n; ++i) {
            update(i, baskets[i], 0, n-1, 0);
        }

        int ans = 0;
        for (auto v: fruits) {
            int pos = query(v, 0, n-1, 0);
            if (pos == -1) ans ++;
            else update(pos, 0, 0, n-1, 0);
        }

        return ans;
    }
};
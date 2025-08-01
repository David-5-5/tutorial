#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.1 树状数组和线段树 - 树状数组
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}
    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }
    // 求区间和 a[l] + ... + a[r], 1 <= l <= r <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        // 参考题解，需要较强的思维能力
        int n = queries.size();
        // 初始前面有 n 个空位置，后面排列 1 .. m
        FenwickTree<int> ft(m + n); // 下标从 1 开始, 按位置标记是否不为空

        // 初始化树状数组，将后 m 个位置标记为 1，表示这些位置已经被访问过。
        vector<int> pos(m+1);    // 记录每个数字在数状数组中的位置 1..m+n
        for (int i = 1; i <= m; ++i) {
            pos[i] = n + i;      // 记录 1..m 在数状数组中的位置
            ft.update(pos[i], 1);
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int & cur = pos[queries[i]];
            ans[i] = ft.pre(cur-1);     // 将该位置的设置为空
            ft.update(cur, -1);
            cur = n - i;                // 更新 queries[i] 的位置到前面
            ft.update(cur, 1);          // 将该位置的设置为非空
        }
        return ans;
    }
};
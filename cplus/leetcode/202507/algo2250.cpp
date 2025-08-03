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
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        // 自行解答 使用树状数组
        int n = points.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {        // idx 按 point x 从大到小排列
            return points[i][0] > points[j][0];
        });
        sort(rectangles.rbegin(), rectangles.rend()); // rectangles 按 x 从大到小排列
        vector<int> ans(n);
        FenwickTree<int> ft(101);        // 1 <= y <= 100
        int j = 0;
        for (int i = 0, j = 0; i < n; ++i) {
            // x 越小越，包含的矩形越多，矩阵的 x >= 点的 x
            while (j < rectangles.size() && rectangles[j][0] >= points[idx[i]][0]) {
                ft.update(rectangles[j++][1], 1);
            }
            // y 越大，包含的矩形越多，矩阵的 y >= 点的 y 的数量
            ans[idx[i]] = j - ft.pre(points[idx[i]][1]-1);
        }
        return ans;

    }
};
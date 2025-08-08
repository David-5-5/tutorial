#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.2 树状数组和线段树 - 逆序对
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
    int reversePairs(vector<int>& record) {
        // 自行解答，复习 使用树状数组
        auto discrete = record;
        sort(discrete.begin(), discrete.end());
        
        int n = record.size(), ans = 0;
        FenwickTree<int> ft(n);
        for (auto r: record) {
            int inx = ranges::lower_bound(discrete, r) - discrete.begin();
            ans += ft.query(inx+2, n);  // inx + 1 为当前值，inx + 2～n 为 大于当前值的数量
            ft.update(inx+1, 1);
        }

        return ans;    
    }
};
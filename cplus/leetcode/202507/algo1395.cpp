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
    int numTeams(vector<int>& rating) {
        // 枚举 j
        int ans = 0, n = rating.size();
        for (int j = 1; j<n-1; ++j) {
            // 统计左边比 rating[j] 小的个数
            int leftSmall = 0, rightBig = 0;
            // 统计右边比 rating[j] 大的个数
            int leftBig = 0, rightSmall = 0;
            for (int i = 0; i<j; ++i) {
                if (rating[i]<rating[j]) {
                    ++leftSmall;
                } else {
                    ++leftBig;
                }
            }
            for (int k = j+1; k<n; ++k) {
                if (rating[k]>rating[j]) {
                    ++rightBig;
                } else {
                    ++rightSmall;
                }
            }
            ans += leftSmall * rightBig + leftBig * rightSmall;
        }
        return ans;
    }


};

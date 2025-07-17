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

    int numTeams2(vector<int>& rating) {
        // 数状数组，优化 left, right
        int ans = 0, n = rating.size();
        auto rating2 = rating;
        sort(rating2.begin(), rating2.end());

        vector<int> leftSmall(n), leftBig(n), rightSmall(n), rightBig(n);
        FenwickTree<int> ft1(n+1);

        for (int j = 0; j<n; ++j) {
            int idx = ranges::lower_bound(rating2, rating[j]) - rating2.begin() + 1;
            leftSmall[j] = ft1.query(1, idx-1);
            leftBig[j] = j - leftSmall[j];
            ft1.update(idx, 1);
        }
        FenwickTree<int> ft2(n+1);
        for (int j = n-1; j>=0; --j) {
            int idx = ranges::lower_bound(rating2, rating[j]) - rating2.begin() + 1;
            rightSmall[j] = ft2.query(1, idx-1);
            rightBig[j] = n - 1 - j - rightSmall[j];
            ft2.update(idx, 1);
        }
        for (int j = 1; j<n-1; ++j) {
            ans += leftSmall[j] * rightBig[j] + leftBig[j] * rightSmall[j];
        }
        
        return ans;
    }

    int numTeams3(vector<int>& rating) {
        // 数状数组，套用 2179 goodTriplets 的方法
        int ans = 0, n = rating.size();
        auto rating2 = rating;
        sort(rating2.begin(), rating2.end());

        FenwickTree<int> ft(n+1);

        for (int j = 0; j<n; ++j) {
            int idx = ranges::lower_bound(rating2, rating[j]) - rating2.begin();
            auto leftSmall = ft.query(1, idx);
            auto leftBig = j - leftSmall;
            auto rightBig = n - 1 - idx - leftBig, rightSmall = n - 1 - j - rightBig;
            ans += leftSmall * rightBig + leftBig * rightSmall;
            ft.update(idx+1, 1);
        }

        return ans;
    }
};

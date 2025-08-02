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
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        // 数状数组，优化 left, right
        long long ans = 0; int n = nums1.size();
        vector<int> left(n), right(n);

        unordered_map<int, int> pos;
        for (int i=0; i<n; ++i) pos[nums1[i]]= i;

        FenwickTree<int> ft_left(n+1);
        for (int j = 0; j<n; ++j) {
            auto y = pos[nums2[j]];
            auto less = ft_left.query(1, y);
            ans += 1LL * less * (n - 1 - y - (j - less));
            ft_left.update(y+1, 1);
        }
        return ans;
    }

    int goodTriplets2(vector<int>& nums1, vector<int>& nums2) {
        // 数状数组，套用 1395 numTeams2 的模板（无需离散化），
        long long ans = 0, n = nums1.size();

        unordered_map<int, int> pos;
        for (int i=0; i<n; ++i) pos[nums1[i]]= i;
        FenwickTree<int> ft1(n+1);
        vector<int> leftSmall(n), rightBig(n);

        for (int j = 0; j<n; ++j) {
            auto idx = pos[nums2[j]];
            leftSmall[j] = ft1.query(1, idx);
            ft1.update(idx+1, 1);
        }
        
        FenwickTree<int> ft2(n+1);
        for (int j = n-1; j>=0; --j) {
            auto idx = pos[nums2[j]];
            rightBig[j] = ft2.query(idx+2, n);
            ft2.update(idx+1, 1);
        }
        for (int j = 1; j<n-1; ++j) {
            ans += (long long) leftSmall[j] * rightBig[j];
        }
        
        return ans;
    }
};


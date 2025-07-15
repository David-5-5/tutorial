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
    int createSortedArray(vector<int>& instructions) {
        // 超时 distance O(n) 时间复杂度，总体 O(n^2)
        const int mod = 1e9 + 7;
        int ans = 0; set<int> st;
        for (auto v: instructions) {
            int left = distance(st.begin(), st.lower_bound(v)); // 
            int right = distance(st.upper_bound(v), st.end());
            ans =  (ans + min(left, right)) % mod; st.insert(v);
        }
        return ans;
    }

    int createSortedArray2(vector<int>& instructions) {
        // 改用 vector ranges::lower_bound ranges::upper_bound，可以通过
        const int mod = 1e9 + 7;
        int ans = 0; vector<int> st;
        for (auto v: instructions) {
            int left = ranges::lower_bound(st, v) - st.begin(); // 
            auto right = ranges::upper_bound(st, v);
            ans =  (ans + min(left, (int)(st.end()-right))) % mod; st.insert(right, v);
        }
        return ans;   
    }



};
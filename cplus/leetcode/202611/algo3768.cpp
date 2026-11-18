#include <bits/stdc++.h>
using namespace std;

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
    long long minInversionCount(vector<int>& nums, int k) {
        // 离散化
        vector<int> uni(nums.begin(), nums.end());
        sort(uni.begin(), uni.end());
        uni.erase(unique(uni.begin(), uni.end()), uni.end());
        unordered_map<int, int> idx;

        int m = uni.size(), n = nums.size();

        for (int i=0; i<m; i++) idx[uni[i]] = i + 1;

        vector<int> suf_ord_cnt(n-k);
        if (n > k) {
            FenwickTree<int> ord(m);
            for (int i=0; i<k; i++) {
                auto val = idx[nums[n-i-1]];
                ord.update(val, 1);
            }
            for (int i=k; i<n; i++) {
                auto pre = idx[nums[n-i-1+k]];
                ord.update(pre, -1);
                auto val = idx[nums[n-i-1]];
                ord.update(val, 1);
                suf_ord_cnt[n-i-1] = ord.pre(val-1);
            }
        }

        long long ans = 0, cur = 0;
        FenwickTree<int> inv(m);
        for (int i=0; i<k; i++) {
            auto val = idx[nums[i]];
            inv.update(val, 1);
            cur += inv.query(val+1, m);
        }
        
        ans = cur;
        for (int i=k; i<n; i++) {
            auto pre = idx[nums[i-k]];
            inv.update(pre, -1);
            cur -= suf_ord_cnt[i-k];
            auto val = idx[nums[i]];
            inv.update(val, 1);
            cur += inv.query(val+1, m);
            ans = min(ans, cur);
        }

        return ans;
    }
};
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
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        FenwickTree<int> ft(101);
        vector<int> ans(nums.size() - k + 1);

        for (int i = 0; i < k-1; ++i) {
            ft.update(nums[i] + 51, 1); // 转换为正数，方便处理
        }

        auto getXth = [&]() -> int {
            // 二分数状数组
            int left = 1, right = 101;
            while (left < right) {
                int mid = (left + right) / 2;
                if (mid > 51) return 0;
                if (ft.query(1, mid) >= x) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            return left - 51; // 转换回原值
        };

        for (int i=k-1; i<nums.size(); ++i) {
            ft.update(nums[i] + 51, 1); // 转换为正数，方便处理
            ans[i-k+1] = getXth();
            ft.update(nums[i-k+1] + 51, -1); // 转换为正数，方便处理
        }
        return ans;   
    }
};
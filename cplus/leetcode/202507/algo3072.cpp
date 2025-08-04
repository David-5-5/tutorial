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
    vector<int> resultArray(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<int> arr1, arr2;

        auto nums2 = nums;
        sort(nums2.begin(), nums2.end());
        
        FenwickTree<int> ft1(n), ft2(n);
        int firstInx = ranges::upper_bound(nums2, nums[0])-nums2.begin();
        int secondInx = ranges::upper_bound(nums2, nums[1])-nums2.begin();
        ft1.update(firstInx, 1); arr1.push_back(nums[0]);   // 这个边界条件设置
        ft2.update(secondInx, 1); arr2.push_back(nums[1]);
        
        for (int i=2; i<n; ++i) {
            int inx = ranges::upper_bound(nums2, nums[i]) - nums2.begin();
            int gc1 = ft1.query(inx+1, n), gc2 = ft2.query(inx+1, n);
            
            if (gc1 > gc2) {
                arr1.push_back(nums[i]);
                ft1.update(inx, 1);
            } else if (gc1 < gc2) {
                arr2.push_back(nums[i]);
                ft2.update(inx, 1);
            } else {
                if (arr1.size() > arr2.size()) {
                    arr2.push_back(nums[i]); ft2.update(inx, 1);
                } else {
                    arr1.push_back(nums[i]); ft1.update(inx, 1);
                }
            }
        }

        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};
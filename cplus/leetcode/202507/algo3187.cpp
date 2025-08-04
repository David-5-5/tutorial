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
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        
        int n = nums.size(); vector<int> peaks(n);
        FenwickTree<int> ft(n); // 1-indexed

        for (int i=1; i<n-1; ++i) {
            if (nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
                peaks[i] = 1;
                ft.update(i+1, 1); // 1-indexed
            }
        }

        vector<int> ans;
        for (auto& q: queries) {
            auto t = q[0], l = q[1], r= q[2];
            if (t == 1) {
                // 求解区间 [l+1 ~ r-1] 子数组的第一个及最后一个元素不是峰值元素
                ans.push_back(ft.query(l+2, r));
            } else {
                nums[l] = r;
                for (int i=0; i<3; ++i) {
                    int j = l + i - 1; 
                    if (j-1 < 0 || j+1>=n) continue;
                    int peak = (nums[j-1] < nums[j] && nums[j] > nums[j+1]) ? 1 : 0;
                    if (peak != peaks[j]) {
                        ft.update(j+1, peak - peaks[j]); // 1-indexed
                        peaks[j] = peak;
                    }
                }
            }
        }
        return ans;
    }
};
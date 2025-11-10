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
            tree[i] = max(tree[i], val);
        }
    }

    // 求前缀最大值 max(a[0], ... a[i])  0 <= i <= n
    T premax(int i) const {
        T res = INT_MIN;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res = max(res, tree[i]);
        }
        return res;
    }

};

class Solution {
public:
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        // 2025.11.07 复习
        int n = nums.size(); long long ans = 0; set<int> num_set;
        
        for (int i=0; i<n; ++i) if (nums[i]>0) num_set.insert(nums[i] - i);
        if (num_set.size() == 0) return ranges::max(nums);

        vector<int> unique_num(num_set.begin(), num_set.end());
        FenwickTree<long long> ft(unique_num.size());

        for (int i=0; i<n; ++i) {
            if (nums[i] <= 0) continue;
            // inx from 1
            int r = ranges::lower_bound(unique_num, nums[i]-i) - unique_num.begin() + 1;

            long long mx = ft.premax(r);
            ft.update(r, mx + nums[i]);
            ans = max(ans, mx + nums[i]);
        }
        return ans;
    }
};


int main() {
    vector<int> nums = {3,3,5,6};
    cout << Solution().maxBalancedSubsequenceSum(nums) << endl;
}
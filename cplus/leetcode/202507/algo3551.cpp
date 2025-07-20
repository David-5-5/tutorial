#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; cc--;
        }
    }
};


class Solution {
public:
    int minSwaps(vector<int>& nums) {
        // 参考题解 - 并查集
        auto digitsum = [](int val) -> int {
            int res = 0;
            while (val) {
                res += val % 10; val /= 10;
            }
            return res;
        };

        int n = nums.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            if (digitsum(nums[i]) == digitsum(nums[j])) return nums[i] < nums[j];
            return digitsum(nums[i]) < digitsum(nums[j]);
        });
        UnionFind uf = UnionFind(n);
        for (int i=0; i<n; ++i) uf.merge(i, idx[i]);
        return n - uf.cc;
    }

    int minSwaps(vector<int>& nums) {
        // 参考题解 - 迭代
        auto digitsum = [](int val) -> int {
            int res = 0;
            while (val) {
                res += val % 10; val /= 10;
            }
            return res;
        };

        int n = nums.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            if (digitsum(nums[i]) == digitsum(nums[j])) return nums[i] < nums[j];
            return digitsum(nums[i]) < digitsum(nums[j]);
        });
        int ans = 0;
        for (int i=0; i<n; ++i) while (i!=idx[i]) {
            ans ++; int v = idx[i]; swap(idx[i], idx[v]);
        };
        return ans;
    }    
};
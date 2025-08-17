#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.3 树状数组和线段树 - 线段树（无区间更新）
class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        const int mod = 1e9 + 7;
        int n = nums.size();
        // 参考 oi-wiki 线段树模板 本题连续字符的最大数
        // 线段树空间, 不包括左边界最大值，不包括右边界的最大值, 不包括左右边界的最大值，区间最大值
        vector<tuple<long, long, long, long>> tree(4 * n);   
        auto maintain = [&] (int p) -> void {
            auto l0 = get<0>(tree[p*2+1]), l1 = get<1>(tree[p*2+1]), l2=get<2>(tree[p*2+1]), l3=get<3>(tree[p*2+1]);
            auto r0 = get<0>(tree[p*2+2]), r1 = get<1>(tree[p*2+2]), r2=get<2>(tree[p*2+2]), r3=get<3>(tree[p*2+2]);
            // 根据 l0,... r0,... 画出图形, 得出其结合的规律
            tree[p] = {max(l2+r3, l0+r0), max(l1+r1, l3+r2), max(l2+r1, l0+r2), max(l3+r0, l1+r3)};
        };

        auto build = [&] (this auto&& build, int start, int end, int p) -> void {
            if (start == end) {
                tree[p] = {0, 0, 0, max(0, nums[start])};  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = start + ((end - start) >> 1);

            build(start, m, p*2+1);
            build(m + 1, end, p*2+2);
            maintain(p);
        };
        

        auto update = [&] (this auto&& update, int l, int val, int start, int end, int p) -> void {
            if (l == start and l == end) {
                tree[p] = {0, 0, 0, max(0, val)};  // 本题用于区间求和 根据题意修改
                return;
            }
            int m = start + ((end - start) >> 1);

            if (l <= m)
                update(l, val, start, m, p*2+1);
            else
                update(l, val, m + 1, end, p*2+2);
            maintain(p);
        };
        // 参考 oi-wiki 
        build(0, n-1, 0);

        int m = queries.size();
        int ans = 0; 
        for (int i=0; i<m; ++i) {
            auto pos = queries[i][0], x = queries[i][1];

            update(pos, x, 0, n-1, 0);
            ans = (ans + get<3>(tree[0])) % mod;
        }
        
        return ans;   

    }
};
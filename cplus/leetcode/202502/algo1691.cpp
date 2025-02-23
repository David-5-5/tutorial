#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        // 参考题解
        // 有点贪心的思路，立方体 A(w1,l1,h1) 可以放在 立方体B (w2,l2,h2)
        // 当且仅当 w1 <= l1 <= h1, w2 <= l2 <= h2, 
        //         w1 < = w2, l1 < = l2, h1 < = h2
        // 注，不需要每个立方体旋转 6 中组合进行比较，因此两两比较的性能提升 36 倍
        // 先是每个立方体内部按照长宽高排序
        // 要求最大的高度，则每个立方体内，最大值作为高度
        for (auto& c: cuboids) sort(c.begin(), c.end());
        // 立方体按照长
        sort(cuboids.begin(), cuboids.end());

        // 以下就是 300 的思路

        int n = cuboids.size(), f[n];
        for (int i=0; i<n; i++) {
            f[i] = 0;
            for (int j=0; j<i; j++) 
                if (cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2])
                    f[i] = max(f[i], f[j]);
            f[i] += cuboids[i][2];
        }

        return *max_element(f, f+n);

    }
};
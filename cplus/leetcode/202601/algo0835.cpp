#include <bits/stdc++.h>
using namespace std;

// 数学算法 七、杂项 - 7.4 多项式
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        // 参考题解，计算每个点之间的偏移量并计数 O(N^4)
        int n = img1.size();
        unordered_map<int, int> offset;

        for (int x1=0; x1<n; ++x1) for (int y1=0; y1<n; ++y1) 
        for (int x2=0; x2<n; ++x2) for (int y2=0; y2<n; ++y2)  {
            if (img1[x1][y1] == 1 && img2[x2][y2] == 1) {
                int off = (x1-x2+n) * 2 * n + (y1-y2+n);
                offset[off] ++;
            }
        }

        int ans = 0;
        for (auto & [_, c]: offset) ans = max(ans, c);
        return ans;
    }
};
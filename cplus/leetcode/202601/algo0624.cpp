#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        // 自行解答，取每个数组中最大值及最小值与前序中的最小值及最大值的差的绝对值
        int mn = arrays[0][0], mx = arrays[0].back(), m = arrays.size(), ans = 0;;
        
        for (int i = 1; i<m; ++i) {
            ans = max(ans, abs(mx - arrays[i][0]));
            ans = max(ans, abs(arrays[i].back() - mn));
            mn = min(arrays[i][0], mn); mx = max(mx, arrays[i].back());
        }
        
        return ans;
    }
};
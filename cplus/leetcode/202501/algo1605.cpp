#include <bits/stdc++.h>
using namespace std;


// 贪心专题 - 构造题
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        // 参考题解，贪心
        // ans[i][j] = min(rowSum[i], colSum[j])
        // 这样保证 ans[i][j] >= 0, sum(ans[i][0]..ans[i][c-1]) == rowSum[i]
        int r = rowSum.size(), c = colSum.size();

        vector<vector<int>> ans(r, vector<int>(c));
        for (int i=0; i<r; i++) {
            for (int j=0; j < c; j++) {
                ans[i][j] = min(rowSum[i], colSum[j]);
                rowSum[i] -= ans[i][j];
                colSum[j] -= ans[i][j];
            }
        }

        return ans;
    }
};
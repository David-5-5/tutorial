#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:

    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        // 参考题解，其实很简单，遍历就可以了 最多 1 << 12 种情况
        int n = aliceArrows.size();

        int mx_score = 0; vector<int> ans(n);

        for (int mask=0; mask< (1<<n); ++mask) {
            int arrows = 0, score = 0; vector<int> res(12);
            for (int i=1; i<n; ++i) {
                if ((mask >> i) & 1) {
                    res[i] = aliceArrows[i] + 1;
                    arrows += aliceArrows[i] + 1;
                    score += i;
                }
                if (arrows <= numArrows && score > mx_score) {
                    mx_score = score, ans = res; ans[0] = numArrows - arrows;
                }
            }
        }

        return ans; 
    }    
};
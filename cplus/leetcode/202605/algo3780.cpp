#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.6 多维 DP
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        vector f(3, vector<int>(3, -1));
        for (auto v: nums) {
            for (int i=2; i>=0; i--) {
                if (i==0) (f[0][v%3] = max(f[0][v%3], v));
                else {
                    for (int j=0; j<3; j++) {
                        if (f[i-1][j] > 0) {
                            f[i][(j+v)%3] = max(f[i][(j+v)%3], f[i-1][j] + v);
                        }
                    }
                }
            }
        }
        return max(0, f[2][0]);   
    }
};
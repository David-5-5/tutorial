#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();

        vector<vector<int>> pres(m+1, vector<int>(n+1));
        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            pres[i+1][j+1] = mat[i][j] + pres[i][j+1] + pres[i+1][j] - pres[i][j];
            
            for (int i1=i,j1=j; i1>=0&&j1>=0; --i1,--j1) {
                if ((pres[i+1][j+1] + pres[i1][j1] - pres[i+1][j1] - pres[i1][j+1]) <=threshold) {
                    ans = max(ans, i-i1+1);
                } else break;
            }
        }

        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

// 周赛 383
class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        // 不需要技巧，暴力计算
        int m = image.size(), n = image[0].size(); 
        
        vector<vector<int>> ans(m,  vector<int>(n));
        vector<vector<int>> cnt(m,  vector<int>(n));

        for (int i=0; i<=m-3; i++)
            for (int j=0; j<=n-3; j++) {
                bool isRegion = true;
                for (int r=i; r<i+3; r++)
                    for (int c=j; c<j+3; c++) {
                        if (r-1 >= i and abs(image[r-1][c] - image[r][c]) > threshold) {
                            isRegion = false;
                            break;
                        }
                        if (c-1 >= j and abs(image[r][c-1] - image[r][c]) > threshold) {
                            isRegion = false;
                            break;
                        }
                    }

                if (isRegion) {
                    int val = 0;
                    for (int r=i; r<i+3; r++)
                        for (int c=j; c<j+3; c++)
                            val += image[r][c];
                    val /= 9;

                    for (int r=i; r<i+3; r++)
                        for (int c=j; c<j+3; c++){
                            ans[r][c] += val;
                            cnt[r][c] ++;
                        }
                }

            }

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                if (cnt[i][j] == 0)
                    ans[i][j] = image[i][j];
                else
                    ans[i][j] /= cnt[i][j];
        
        return ans;
    }
};
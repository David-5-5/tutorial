#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        // 自行解答，矩阵对角线遍历
        int m = mat.size(), n = mat[0].size();
        vector<int> ans;

        int r = 0, c = 0, r_step = -1, c_step = 1;
        while (r + c < m + n - 1) {
            if (r >=0 && r < m && c >=0 && c < n) {
                ans.push_back(mat[r][c]);
                r += r_step; c += c_step;
            } else {
                r ++;
                r_step *= -1; c_step *= -1;
                while (r + c < m + n - 1 && !(r >=0 && r < m && c >=0 && c < n)) {
                    r += r_step; c += c_step;
                }
            }
        }

        return ans;  
    }
};

int main() {
    vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
    Solution().findDiagonalOrder(mat);
}
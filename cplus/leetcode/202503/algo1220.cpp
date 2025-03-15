#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  矩阵快速幂优化 DP
class Solution {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;

        // 矩阵快速幂 模板
        auto pow = [&](vector<vector<int>> a, vector<vector<int>> b) -> vector<vector<int>> {
            int r = a.size(), m = a[0].size(), c = b[0].size();
            vector<vector<int>> res(r, vector<int>(c));
            for (int i=0; i<r; i++) {
                for (int j=0; j<c; j++)
                    for (int k=0; k<m; k++)
                        res[i][j] = (res[i][j] + (long)a[i][k] * b[k][j]) % MOD;
            }
            return res;
        };
        vector<vector<int>> trans = {{0, 1, 0, 0, 0}, {1, 0 , 1, 0, 0}, {1, 1 , 0, 1, 1}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 0}};
        vector<vector<int>> result = {{1}, {1}, {1}, {1}, {1}};

        vector<vector<int>> ans = {{1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0}, {0, 0, 0, 0, 1}};   
        int k = n - 1;
        while (k) {
            if ((k & 1)== 1)
                ans = pow(trans, ans);
            trans = pow(trans, trans);
            k = k >> 1;
        }

        auto res = pow(ans, result);
        int sum = 0;
        for (auto& r : res) sum = (sum + r[0])% MOD;
        return sum;

    }
};
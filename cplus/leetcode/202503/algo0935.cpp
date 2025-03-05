#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int knightDialer(int n) {
        const int mod = 1e9 + 7;
        vector<int> move[10];
        move[0] = {4, 6};
        move[1] = {6, 8};
        move[2] = {7, 9};
        move[3] = {4, 8};
        move[4] = {0, 3, 9};
        move[6] = {0, 1, 7};
        move[7] = {2, 6};
        move[8] = {1, 3};
        move[9] = {2, 4};

        vector<vector<int>> memo(10, vector<int>(n+1, -1));
        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (j == 1) return 1;

            auto& res = memo[i][j];
            if (res != -1) return res;
            res = 0;
            for (auto& x:move[i]) {
                res = (res + dfs(x, j-1))% mod;
            }

            return res;
        };

        int ans = 0;
        for (int i=0; i<10; i++) {
            ans = (ans + dfs(i, n)) % mod;
        }

        return ans;     
    }
};
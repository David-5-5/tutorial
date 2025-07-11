#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int numOfWays(int n) {
        // 自行解答，数学方法
        // 起初两种颜色方案 6 种，三种颜色方案是 6
        // 两种颜色的方案的下一行是 5 种方案，col2 * 5，其中 col2 * 3 是两种颜色，col2 * 2 是三种颜色
        // 三种种颜色的方案的下一行是 4 种方案，col3 * 4，其中 col3 * 2 是两种颜色，col3 * 2 是三种颜色
        const int mod = 1e9 + 7;
        int col2 = 6, col3 = 6;
        for (int _=0; _<n-1; _++) {
            int new_col2 = ((long)col2 * 3 + col3 * 2) % mod;
            int new_col3 = ((long)col2 * 2 + col3 * 2) % mod;
            col2 = new_col2, col3 = new_col3;
        }

        return ((long)col2 + col3) % mod;
    }

    int numOfWays2(int n) {
        // 参考题意 记忆化搜索
        const int mod = 1e9 + 7;
        vector<int> types;
        for (int i=0; i<3; ++i)for (int j=0; j<3; ++j)for (int k=0; k<3; ++k) {
            if (i != j && j != k) {
                types.push_back(i*9 + j*3 + k); // 三进制数
            }
        }
        
        auto relate = [](int i, int j) -> bool {
            if (i == 0 || j == 0) return true;
            // correct
            if (i / 9 == j / 9) return false;
            if ((i / 3 % 3) == (j / 3 % 3)) return false;
            if (i % 3 == j % 3) return false;
            
            // if (i / 9 == j / 9) return false;
            // i %= 9, j %= 9;
            // if (i / 3 == j / 3) return false;
            // i %= 3, j %= 3;
            // if (i == j) return false;
            return true;
        };

        vector<vector<int>> memo(n, vector<int>(27, -1));
        auto dfs = [&](this auto&& dfs, int i, int prev) -> int {
            if (i == n) return 1;

            auto& res = memo[i][prev];
            if (res != -1) return res;
            
            res = 0;
            for (auto& v: types) 
                if (relate(v, prev)) res = ((long)res + dfs(i+1, v)) % mod;
            return res;
        };

        return dfs(0, 0);
        
    } 

    int numOfWays3(int n) {
        // 类似于 numOfWays2, 数组代替函数
        const int mod = 1e9 + 7;
        vector<int> types;
        for (int i=0; i<3; ++i)for (int j=0; j<3; ++j)for (int k=0; k<3; ++k) {
            if (i != j && j != k) {
                types.push_back(i*9 + j*3 + k); // 三进制数
            }
        }
        
        vector<vector<int>> relate(27, vector<int>(27));
        for (int i=0; i<12; ++i) for (int j=0;j<12; ++j) {
            int u = types[i], v = types[j];
            if ((u / 9 != v / 9) && (u / 3 % 3 != v / 3 % 3) && (u % 3 != v % 3)) 
                relate[u][v] = 1;
        }

        vector<vector<int>> memo(n, vector<int>(27, -1));
        auto dfs = [&](this auto&& dfs, int i, int prev) -> int {
            if (i == n) return 1;

            auto& res = memo[i][prev];
            if (res != -1) return res;
            
            res = 0;
            for (auto& v: types) 
                if (prev == 0 || relate[prev][v]) res = ((long)res + dfs(i+1, v)) % mod;
            
            return res;
        };

        return dfs(0, 0);
    }    

};
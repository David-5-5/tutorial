#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP

// Beging prepare for numTilePossibilities2
const int MX = 8;
int c[MX][MX];
int init = [] () {
    for (int i=0; i<MX; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j=1; j<i; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j]; // 组合数
        }
    }
    return 0;
}();
// End

class Solution {
public:
    int numTilePossibilities(string tiles) {
        // 参考题解，回溯
        int n = tiles.length();
        unordered_map<char, int> count;
        set<char> tset;
        for (char ch : tiles) {
            count[ch] ++;
            tset.insert(ch);
        }

        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == 0) return 1;

            int res = 1;     // 每个长度都计数
            for (auto& ch : tset) {
                if (count[ch]) {
                    count[ch] --;
                    res += dfs(i-1);
                    count[ch] ++;
                }
            }
            return res;
        };

        return dfs(n) - 1;

    }

    int numTilePossibilities2(string tiles) {
        unordered_map<char, int> count;
        for (char ch : tiles) count[ch] ++;
        int n = tiles.length(), m = count.size(), f[m + 1][n + 1];
        memset(f, 0, sizeof(f));
        f[0][0] = 1; // 构造空序列的方案数

        int i = 1;
        for (auto &[_, cnt]: count) {
            for (int j=0; j<=n; j++) 
                for (int k=0; k<=j && k<=cnt; k++) 
                    f[i][j] += f[i-1][j-k] * c[j][k];
            i++;
        }

        return accumulate(f[m] + 1, f[m] + n + 1, 0);
    }

};
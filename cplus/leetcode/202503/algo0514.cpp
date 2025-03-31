#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        // 参考题解 此题的关键在于计算循环数组的 left 和 right
        int n = ring.length(), m = key.length();

        // 计算每个字母的最后一次出现的下标，
        // 循环数组计算每个
        // !!! Elgant Elgant Elgant!!!
        array<int, 26> pos;
        for (int i=0; i<n; ++i) ring[i] -= 'a', pos[ring[i]] = i;

        vector<array<int, 26>> left(n);
        for (int i=0; i<n; ++i) {
            left[i] = pos;
            pos[ring[i]] = i;   // 更新下标
        }

        for (int i=n-1; i>=0; --i) pos[ring[i]] = i;
        vector<array<int, 26>> right(n);
        for (int i=n-1; i>=0; --i) {
            right[i] = pos;
            pos[ring[i]] = i;
        }
        // !!! Elgant Elgant Elgant!!!


        vector<vector<int>> memo(m, vector<int>(n, -1));
        auto dfs = [&](this auto&& dfs, int j, int i) -> int {
            if (j == m) return 0;

            auto& res = memo[j][i];
            if (res != -1) return res;

            res = INT_MAX;
            char c = key[j] - 'a';
            if (c == ring[i]) return res = dfs(j+1, i);

            int l = left[i][c], r = right[i][c];
            return res = min(dfs(j+1, l) + (l>i ? n-l+i : i-l),
                             dfs(j+1, r) + (r<i ? n-i+r : r-i));

        };

        return dfs(0, 0) + m;

    }
};
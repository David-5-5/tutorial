#include <bits/stdc++.h>
using namespace std;

// LCR series 同 233
class Solution {
public:
    int digitOneInNumber(int num) {
        string s = to_string(num);
        int n = s.size();

        // 记忆化数组：[位置][1的个数][是否受限] = 计算结果
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(n + 1, vector<int>(2, -1)));

        function<int(int, int, bool)> f = [&](int i, int cnt1, bool is_limit) -> int {
            // 递归终点
            if (i == n) {
                return cnt1;
            }
            // 记忆化剪枝
            if (memo[i][cnt1][is_limit] != -1) {
                return memo[i][cnt1][is_limit];
            }

            int res = 0;
            int up = is_limit ? (s[i] - '0') : 9;

            // 枚举 0 ~ up
            for (int d = 0; d <= up; d++) {
                res += f(i + 1, cnt1 + (d == 1), is_limit && (d == up));
            }

            // 存入记忆
            return memo[i][cnt1][is_limit] = res;
        };

        return f(0, 0, true);
    }
};
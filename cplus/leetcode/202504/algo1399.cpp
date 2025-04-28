#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int countLargestGroup(int n) {
        // 自行解答 O(n) 暴力做法
        unordered_map<int, int> cnt;
        int ans = 0;

        for (int i=1; i<=n; i++) {
            int v = i, sum = 0;
            while (v) {
                sum += v % 10;
                v /= 10;
            }
            cnt[sum] ++;
        }

        int mx = 0, mx_cnt = 0;
        for (auto& [_, v]: cnt) {
            if (v>mx) mx = v, mx_cnt = 1;
            else if (v == mx) mx_cnt += 1;
        }
        return mx_cnt;
    }

    int countLargestGroup2(int n) {
        // 复习 数位DP
        string s = to_string(n);
        int m = s.length();
        // 参考题解 数位 DP
        vector<vector<int>> memo(m, vector<int>(9*m+1, -1));

        auto f = [&] (this auto&& f, int i, int target, bool limit) -> int {
            if (target<0) return 0;
            if (i == m) return target==0;

            if (!limit && memo[i][target]!= -1) return memo[i][target];

            int res = 0;
            int up = limit?s[i]-'0':9;
            for (int d=0; d<=up; ++d) {
                res += f(i+1, target-d,limit && d==up);
            }
            if (!limit) memo[i][target]=res;
            return res;
        };

        int mx_cnt = 0, ans = 0;
        for (int t=1; t<=9*m; t++) {
            int cnt = f(0, t, true);
            if (cnt > mx_cnt) {
                mx_cnt = cnt, ans = 1;
            } else if (cnt == mx_cnt) ans ++;
        }
        return ans;
    }
};
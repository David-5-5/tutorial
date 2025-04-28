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

};
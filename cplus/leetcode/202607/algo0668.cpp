#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        // 自行解答，二分，
        // 灵光一现，猜一个数，计算每行小于该数的数量

        auto check = [&] (int val) -> pair<int, int> {
            // 矩阵中 cnt 是小于等于 val, 矩阵 le 是小于等于 val 的值
            // 例如 m = 5, n = 3, val = 13， 
            // 矩阵中不存在两数相乘等于 13 的数，le = 12 是小于等于 13 的最大值
            int le = 0, cnt = 0;    
            for (int i=1; i<=m; i++) {
                auto c = min(n, val / i);
                le = max(le, c * i);
                if (c == 0) break;  // 剪枝
                cnt += c;
            }

            return {cnt, le};
        };

        int left = 0, right = m * n + 1, ans = 0;
        while (left + 1 < right) {
            auto mid = (left + right) / 2;
            auto [cnt, le] = check(mid);
            if (cnt >= k) {
                ans = le; right = mid;
            } else {
                left = mid;
            }
        }
        return right;   
    }


};
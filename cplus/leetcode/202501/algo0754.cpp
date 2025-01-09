#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他数学贪心
class Solution {
public:
    int reachNumber(int target) {
        // 自行解答 找规律，大于 target 的前缀和同时前缀和 - target 是偶数
        // 将 (sum - target) / 2 符号反转，前 n 个数的前缀和即为 target
        if (target < 0) target = - target; // 正负数对称，转换为正数统一处理
        int n = 1;
        long sum = n * (n+1) / 2;
        while ((sum-target) % 2 == 1 or sum < target) {
            n += 1;
            sum = n * (n+1) / 2;
        }
        return n;
    }
};
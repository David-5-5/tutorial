#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(int n) {
        // 参考题解 位运算技巧
        int ans = 1;
        while (n & (n-1)) {
            // lowbit 
            auto lb = n & (~n + 1); //n & -n;
            if (n & (lb << 1)) n += lb; // 有连续加上 lowbit
            else n -= lb;               // 没有连续减去 lowbit
            ans ++;
        }
        return ans;
    }

    int minOperations2(int n) {
        // 参考题解 
        return __builtin_popcount(3 * n ^ n);
    } 

    int minOperations3(int n) {
        // 参考题解 
        auto dfs = [] (this auto&& dfs, long long val) -> int {
            if ((val & (val-1)) == 0) return 1;
            auto lb = val & -val;
            return 1 + min(dfs(val + lb), dfs(val - lb));
        };

        return dfs(n);
    }
    
};
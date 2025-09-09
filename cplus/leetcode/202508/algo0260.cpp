#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // 参考题解 位运算
        int x = 0;
        for (auto val:nums) x ^= val;
        
        // 位运算，最小值 INT_MIN 的 lowbit 仍是其本身
        auto lb = (x == INT_MIN)?x:x & -x; // x&(~n+1)
        int x1 = 0, x2 = 0;
        for (auto val: nums) if (val & lb) x1 ^= val; else x2 ^= val;
        return {x1, x2};  
    }
};
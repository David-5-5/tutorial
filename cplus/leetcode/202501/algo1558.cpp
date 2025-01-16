#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 逆向思维
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // 自行解答 
        int mx = ranges::max(nums), ans = 0;
        for (auto v:nums)
            ans += __builtin_popcount(v); // + 操作是每个数的 二进制 1 的数量
        
        int bit = 0;
        for (int i=31;i>0;i--) // 乘 2 操作是最大数最高位移位到 1 次数
            if (mx >> i & 1) {
                bit = i;
                break;
            }

        ans += bit;
        return ans;
        
    }
    
    int minOperations2(vector<int>& nums) {
        int mx = ranges::max(nums), ans = 0;
        for (auto v:nums)
            ans += __builtin_popcount(v);
        // 使用 while
        while (mx>1) 
            ans ++, mx >>= 1;

        return ans;
                
    }
};
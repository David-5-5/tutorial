#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int xor_sum = 0, n = nums.size(); bool non_zero = false;
        for (auto & v : nums) {
            xor_sum ^= v;
            if (v) non_zero = true;
        }
        // 计算全部数组的xor和,不为0 即为全部长度
        // 如果存在非零数，减少一个非零数，否则全为 0, 不存在非零xor和，返回 0
        if (xor_sum) return n;      
        else return non_zero?n-1:0; 
    }
};
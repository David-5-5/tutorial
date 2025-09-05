#include <bits/stdc++.h>
using namespace std;

// 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        // 自行解答 复习 不存在的一定都是 2 的幂 
        unordered_set<int> hash_nums(nums.begin(), nums.end());
        for (int i=0; i<32; ++i) 
            if (!hash_nums.count(1<<i)) return 1<<i;

        return 1;
    }

    int minImpossibleOR(vector<int>& nums) {
        // 进一步优化 lowbit
        int mask = 0;
        for (auto& v: nums) if ((v&(v-1)) == 0) mask |= v;
        
        mask = ~mask;
        return mask & (-mask); // lowbit
    }    
};
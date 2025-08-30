#include <bits/stdc++.h>
using namespace std;

// 位运算 - 异或（XOR）的性质
class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        // 自行解答
        int cnt[20], n = nums.size(); // 按位累计 1 的个树，奇数表示改为的 1
        memset(cnt, 0, sizeof(cnt));

        vector<int> ans(n);
        for (int i = 0; i<n; ++i) {
            auto num = nums[i];
            int b = 0; // 当前位
            while(num) {
                if (num & 1) cnt[b]++;
                b ++; num >>= 1;    
            }

            for (int bit=0; bit<maximumBit; ++bit) {
                if (cnt[bit] % 2 == 0) ans[n-1-i] += 1 << bit;
            }
        }
        
        return ans;
    }

    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        // 自行解答，优化后 不需要统计每位的 1 的数量，直接进行异或操作即可
        // vector<int> ans; int mask = 0;
        // for (auto & num: nums) {
        //     mask ^= num;
        //     ans.push_back(mask ^ ((1<<maximumBit)-1));
        // }
        // reverse(ans.begin(), ans.end());
        // return ans;

        // 不用 reverse, 性能更优
        int mask = 0, n=nums.size();
        vector<int> ans(n); 
        for (int i=0; i<n; ++i) {
            mask ^= nums[i];
            ans[n-1-i] = mask ^ ((1<<maximumBit)-1);
        }
        return ans;
    }    
};
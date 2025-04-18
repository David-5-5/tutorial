#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        // 参考题解 被 nums.size() 迷惑了，值域是 1 <= nums[i] <= 30
        // 最后时间复杂度 O(30*2^10*log2^10) 而不是 O(10^5*2^10*log2^10)= O(10^8)
        const array<int, 10> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        const int mod = 1e9 + 7, num_max = 30;
        
        vector<int> freq(num_max + 1);
        for (int num: nums) {
            ++freq[num];
        }

        vector<int> f(1 << primes.size());
        f[0] = 1;
        for (int _ = 0; _ < freq[1]; ++_) {
            // 对每个1都是选或不选，每个1两种情况，n个1就是 2^n 种情况
            f[0] = f[0] * 2 % mod;  
        }
        
        for (int i = 2; i <= num_max; ++i) {
            if (freq[i] == 0) { // 这样写比 !freq[i] 更直观
                continue;
            }
            
            // 检查 i 的每个质因数是否均不超过 1 个
            int subset = 0, x = i;
            bool check = true;
            for (int j = 0; j < primes.size(); ++j) {
                int prime = primes[j];
                // 类似4 , 9 值域比较小，可以hardcode
                if (x % (prime * prime) == 0) { 
                    check = false;
                    break;
                }
                if (x % prime == 0) {
                    subset |= (1 << j); //包含的质数
                }
            }
            if (!check) {
                continue;
            }

            // 动态规划
            for (int mask = (1 << primes.size()) - 1; mask > 0; --mask) {
                if ((mask & subset) == subset) {    // 对每个状态的遍历其子集
                    f[mask] = (f[mask] + static_cast<long long>(f[mask ^ subset]) * freq[i]) % mod;
                }
            }
        }

        int ans = 0;
        for (int mask = 1, mask_max = (1 << primes.size()); mask < mask_max; ++mask) {
            ans = (ans + f[mask]) % mod;
        }
        
        return ans; 

    }
};
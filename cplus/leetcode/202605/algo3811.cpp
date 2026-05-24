#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        // 自行解答
        const int mod = 1e9 + 7;
        int n = nums.size();
        unordered_map<long long, int> memo;
        auto dfs = [&](this auto&& dfs, int i, int s_xor, int exp) -> int {
            if (i == n-1) return s_xor == (exp==0?target1:target2);
            long long mask =  1LL * s_xor << 32 | i << 1 | exp;
            if (memo.count(mask)) return memo[mask];
            
            long long res = dfs(i+1, s_xor ^ nums[i+1], exp);
            if (s_xor == (exp==0?target1:target2)) res += dfs(i+1, nums[i+1], exp^1);
            return memo[mask] = res % mod;
        };

        return dfs(0, nums[0], 0);      
    }
};
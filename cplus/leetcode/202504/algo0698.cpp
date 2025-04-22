#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k) return false;
        int group = sum / k;

        int n = nums.size();
        cout << (1 << n) << ", " << group << endl;
        unordered_map<int,bool> memo;
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i == 0 && j == 0) return true;
            int mask = i<<16 | j;

            if (memo.count(mask)) return memo[mask];

            for (int x=0; x<n; x++) {
                
                if ((i >> x & 1) && nums[x]+j <= group){
                    memo[mask] = dfs(i-(1<<x), (nums[x]+j)%group);
                }
                if (memo[mask]) return true;
            }
            return memo[mask]=false;
        };

        return dfs((1<<n)-1, 0);    

    }
};
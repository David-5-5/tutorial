#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        // 自行解答
        int  n = nums.size(), m = 1 << target.size();
        
        vector<long> comb(m, 1);
        for (int i=0; i<target.size(); ++i) {
            int low = 1 << i;
            for (int j=0; j<low; ++j) 
                comb[j|1<<i] = lcm(comb[j], target[i]);
        }

        vector<vector<long>> dp(n+1, vector<long>(m, INT_MAX/2));
        // for (int i=0; i<=n; i++) dp[i][0] = true;
        dp[0][0] = 0;

        for (int i=0; i<n; ++i) {
            dp[i+1] = dp[i];
            for (int mask=0; mask<m; ++mask) {
                if (dp[i][mask]>=INT_MAX/2) continue;
                
                int exclusive = m - 1 - mask;   // mask 补集的子集遍历
                int sub = exclusive;
                while (sub) {
                    long inc = (comb[sub]-(nums[i]%comb[sub])) % comb[sub];
                    if (inc < 0) 
                        cout << comb[sub] << ", " << nums[i] << endl;
                    dp[i+1][mask|sub] = min(dp[i+1][mask|sub], dp[i][mask]+inc);
                    sub = (sub-1) & exclusive;  // 子集遍历
                }
            }
        }
        return dp[n][m-1];   
    }
};

int main() {
    vector<int> nums = {1,2,3}, target = {4};
    cout << Solution().minimumIncrements(nums, target) << endl;
}
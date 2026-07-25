#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.6 SOS DP
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int mx = nums[0], n = nums.size();
        for (int i=1; i<n; i++) mx = max(mx, nums[i]);
        int bw = bit_width((unsigned) mx);

        auto tot = (1 << bw) - 1;
        vector<int> dp(tot + 1);

        for (auto x: nums) dp[x] = x;

        for (int s=1; s<=tot; s++) {
            auto t = s;             // 状态
            auto lb = t & -t;
            while (lb) {
                dp[s] = max(dp[s], dp[s^lb]);
                t = t ^ lb; lb = t & -t;
            }
        }

        long long ans = 0;

        for (auto x : nums) {
            ans = max(ans, 1LL * x * dp[tot - x]);
        }
        return ans;
    }

    long long maxProduct2(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        int bw = bit_width((unsigned) mx);  // bw 维

        // 高维前缀和模板
        auto tot = (1 << bw) - 1;
        vector<int> dp(tot + 1);

        for (auto x: nums) dp[x] = x;

        for (int i=0; i<bw; i++) {
            for (int j=0; j<(1<<bw); j++) {
                if (j >> i & 1) dp[j] = max(dp[j], dp[j^(1<<i)]);
            }
        }

        long long ans = 0;
        for (auto x : nums) {
            ans = max(ans, 1LL * x * dp[tot - x]);
        }
        return ans;
    }    
};

int main() {
    vector<int> nums = {64,8,32};
    cout << Solution().maxProduct(nums) << endl;
}
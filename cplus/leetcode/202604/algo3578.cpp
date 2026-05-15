#include <bits/stdc++.h>
using namespace std;

// 五、划分型 DP - 5.2 最优划分
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        // 参考题解 前缀和优化 滑动窗口最大值 最小值
        const int mod = 1e9 + 7;
        deque<int> inc, asc;    
        int n = nums.size(); vector<int> dp(n+1); dp[0] = 1;

        int l = 0, sum = 0;
        for (int i=0; i<n; i++) {
            sum = (sum + dp[i]) % mod;
            while (inc.size() && nums[inc.back()] < nums[i]) inc.pop_back();
            inc.push_back(i);
            while (asc.size() && nums[asc.back()] > nums[i]) asc.pop_back();
            asc.push_back(i);

            while (nums[inc.front()] - nums[asc.front()] > k) {
                sum = (mod + sum - dp[l++]) % mod;
                if (inc.front() < l) inc.pop_front();
                if (asc.front() < l) asc.pop_front();
            }
            dp[i+1] = sum;
        }
        return dp[n];
    }
};

int main() {
    vector<int> nums = {9,4,1,3,7};
    cout << Solution().countPartitions(nums, 4) << endl;
}
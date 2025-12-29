#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 三、背包 3.2 完全背包
class Solution {
public:
    vector<int> findCoins(vector<int>& numWays) {
        // 自行解答 
        int n = numWays.size(); vector<int> ans;

        for (int i=1; i<=n; i++) {
            vector<int> dp(i+1); dp[0] = 1; // 每次循环重新计算 dp
            for (int j=0; j<ans.size(); j++) {
                for (int k=ans[j]; k<=i; k++) {
                    dp[k] += dp[k-ans[j]];
                }
            }

            if (dp[i] < numWays[i-1]) {
                ans.push_back(i); dp[i] += 1;
            }

            if (dp[i]!=numWays[i-1]) return {};
        }

        return ans;
    }

    vector<int> findCoins2(vector<int>& numWays) {
        // 自行解答 - 优化实现
        int n = numWays.size(); vector<int> ans, dp(n+1); dp[0] = 1;

        for (int i=1; i<=n; i++) {
            if (dp[i] == numWays[i-1]) continue;

            for (int k=i; k<=n; k++) {
                dp[k] += dp[k-i];
            }
            if (dp[i] != numWays[i-1]) return {};
            ans.push_back(i);
        }

        return ans;
    }    
};

int main() {
    vector<int> numWay = {0,1,0,2,0,3,0,4,0,5};
    Solution().findCoins(numWay);
}
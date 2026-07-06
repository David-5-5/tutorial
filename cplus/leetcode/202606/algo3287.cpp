#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        // pre[i][j][x] 前 i 个元素，选择 j 个的 或为 x 是否存在？
        // suf[i][j][x] 后 i 个元素，选择 j 个的 或为 x 是否存在？
        int n = nums.size(), m = reduce(nums.begin(), nums.end(), 0, bit_or<>());

        vector pre(n-k+1, vector(k+1, vector<bool>(m+1)));
        vector suf(n-k+1, vector(k+1, vector<bool>(m+1)));
        pre[0][0][0] = true, suf[0][0][0] = true;

        for (int i=0; i<n-k; i++)  for (int j=0; j<=k; j++) 
            for (int x=0; x<=m; x++) {
                if (pre[i][j][x]) {
                    pre[i+1][j][x] = pre[i][j][x]; // 不选
                    if (j<k) pre[i+1][j+1][x|nums[i]] = pre[i][j][x];
                }
                if (suf[i][j][x]) {
                    suf[i+1][j][x] = suf[i][j][x]; // 不选
                    if (j<k) suf[i+1][j+1][x|nums[n-1-i]] = suf[i][j][x];
                }
            }
        
        int ans = 0;
        for (int i=k; i<=n-k; i++) {
            for (int x=0; x<=m; x++)  for (int y=0; y<=m; y++) {
                if (pre[i][k][x] && suf[n-i][k][y]) ans = max(ans, x ^ y);
            }
        }
        return ans;
    }

    int maxValue2(vector<int>& nums, int k) {
        // 降维
        int n = nums.size(), m = reduce(nums.begin(), nums.end(), 0, bit_or<>());

        vector dp(k+1, vector<bool>(m+1));
        vector suf(n-k+1, vector<bool>(m+1));
        dp[0][0] = true;

        for (int i=0; i<n-k; i++) for (int j=k; j>=0; j--) {
            for (int x=m; x>=0; x--) {
                if (dp[j][x] && j<k) {
                    dp[j+1][x|nums[n-1-i]] = dp[j][x];
                }
            }
            if (i+1>=k) suf[i+1] = dp[k];
        }
        int ans = 0;
        for (auto& row : dp) {
            fill(row.begin(), row.end(), false);
        }

        dp[0][0] = true;
        for (int i=0; i<n-k; i++) {
            for (int j=k; j>=0; j--)  for (int x=m; x>=0; x--) {
                if (dp[j][x] && j<k) {
                    dp[j+1][x|nums[i]] = dp[j][x];
                }
            }
            if (i+1>=k)  {
                for (int x=0; x<=m; x++)  for (int y=0; y<=m; y++) {
                    if (dp[k][x] && suf[n-1-i][y]) ans = max(ans, x ^ y);
                }
            }
        }
        return ans;
    }  
};

int main() {
    vector<int> nums = {2, 6, 7};
    cout << Solution().maxValue(nums, 1) << endl;
}
#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        // 参考题解 状态 dp
        int n = nums.size();

        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (auto& target:st) {
            int f0 = 0, f1 = 0, f2 = 0;
            for (auto& x : nums)  {                 // 状态转移方程
                f2 = max(f2, f1) + (x==k);          // 在子数组右，左+中+右
                f1 = max(f1, f0) + (x == target);   // 在子数组中，左+中
                f0 += (x == k);                     // 在子数组左，左
            }
            ans = max({ans, f1, f2});
        }

        return ans;

    }

    int maxFrequency2(vector<int>& nums, int k) {
        // 参考题解 贪心 
        int n = nums.size();
        
        // nums 等于 k 的前缀和
        int f[n+1];
        f[0] = 0;
        for (int i=0; i<n; i++) {
            f[i+1] = f[i];
            if (nums[i] == k) f[i+1] ++;
        }

        // 记录每种 k - x 的下标
        unordered_map<int, vector<int>> pos;
        for (int i=1; i<=n; i++) {
            int d = k - nums[i-1];
            pos[d].push_back(i);
        }

        int ans = 0;
        for (auto& x : pos) {
            auto& p = x.second;
            int mx = -1e9;
            for (int i=0; i<p.size(); i++) {
                mx = max(mx, f[p[i]-1] - i + 1);
                ans = max(ans, f[n] - f[p[i]] + i + mx);
            }
        }

        return ans;
    }    
};
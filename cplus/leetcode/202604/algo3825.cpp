#include <bits/stdc++.h>
using namespace std;

// 四、经典线性 DP 4.2 最长递增子序列（LIS） 4.2.2 进阶
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        auto LIS = [&] (vector<int>& arr) -> int {
            // 300 题 O(NlogN) 二分做法
            vector<int> ans;
            for (auto& v: arr) {
                int idx = ranges::lower_bound(ans, v) - ans.begin();
                if (idx == ans.size()) ans.push_back(v);
                else ans[idx] = v;
            }
            return ans.size();            
        };

        int ans = 0;
        for (int i = 0; i<32; i++) {
            vector<int> arr; 
            for (auto v: nums) if ((v >> i) & 1) arr.push_back(v);
            ans = max(ans, LIS(arr));
        }
        return ans;
    }
};
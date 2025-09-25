#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        // 自行解答
        int n = nums.size(); vector<int> ans(n, -1);
        long long sum = 0;
        if (n<(2*k+1)) return ans;
        for (int i=0; i<2*k; i++) sum += nums[i];
        for (int i=k; i<n-k; i++) {
            sum += nums[i+k];
            ans[i] = sum / (2*k + 1);
            sum -= nums[i-k];
        }
        return ans;     
    }
};
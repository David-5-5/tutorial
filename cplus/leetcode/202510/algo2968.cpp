#include <bits/stdc++.h>
using namespace std;

// # 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution {
public:
    int maxFrequencyScore(vector<int>& nums, int k) {
        // 2025.10.10 复习
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // 计算前缀和
        vector<long long> pres(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pres[i + 1] = pres[i] + nums[i];
        }
        
        // 计算区间[l, r]转换为中位数所需的代价
        auto diff = [&](int l, int r) -> long long {
            if (l == r) return 0;
            int mid = (l + r) / 2;
            return pres[r+1] + pres[l] - pres[mid+1] - pres[mid] + nums[mid] * (2*mid-l-r);
        };
        
        int ans = 0;
        int left = 0;
        
        // 滑动窗口寻找最大长度
        for (int right = 0; right < n; ++right) {
            // 当代价超过k时，移动左指针
            while (diff(left, right) > k) {
                left++;
            }
            // 更新最大窗口长度
            ans = max(ans, right - left + 1);
        }
        
        return ans;   
    }
};
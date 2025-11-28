#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        // 自行解答
        int i = 1, n = nums.size();

        auto sum = [&](int l, int p, int q, int r) -> long long {
            long long res = 0, mx = LONG_LONG_MIN, pre = 0;
            for (int i=p-1; i>=l; --i) {
                pre += nums[i];
                if (pre > mx) mx = pre;
            }
            res += mx;
            mx = INT_MIN, pre = 0;
            for (int i=q+1; i<=r; ++i) {
                pre += nums[i];
                if (pre > mx) mx = pre;
            }
            res += mx;
            for (int i = p; i<= q; ++i) res += nums[i];
            return res;
        };
        
        long long ans = LONG_LONG_MIN;
        int l = -1, p = -1, q = -1, r = -1;
        while (i < n) {
            if (l == -1) {
                while (i<n && nums[i-1]>=nums[i]) i++;
                l = i-1;
                while (i<n && nums[i-1]<nums[i]) i++;         // 最大化 p
                p = i-1;
            }
            // 相等重新从 l 开始
            if (i<n && nums[i-1] == nums[i])  {l = -1; i++; continue;}    
            while (i<n && nums[i-1]>nums[i]) i++;         // 最大化 p
            q = i-1;
            // 相等重新从 l 开始
            if (i<n && nums[i-1] == nums[i])  {l = -1; i++; continue;}    
            while (i<n && nums[i-1]<nums[i]) i++;
            r = i-1;
            if (r > q) ans = max(ans, sum(l, p, q, r));
            l = q, p = r, q = -1, r = -1;
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {0,-2,-1,-3,0,2,-1};
    cout << Solution().maxSumTrionic(nums) << endl;
}
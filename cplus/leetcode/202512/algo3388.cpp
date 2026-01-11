#include <bits/stdc++.h>
using namespace std;

// 字符串 - 二、Z 函数（后缀的前缀）
class Solution {
public:
    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        // z 函数 模板
        auto zFunc = [&](int offset) -> vector<int>{
            int t_len = n - offset;
            vector<int> ans(t_len);
            for (int i = 1, l = 0, r = 0; i < t_len; ++i) {
                if (i <= r && ans[i - l] < r - i + 1) {
                    ans[i] = ans[i - l];
                } else {
                    ans[i] = max(0, r - i + 1);
                    while (i + ans[i] < t_len && nums[offset + ans[i]] == nums[offset + i + ans[i]]) ++ans[i];
                }
                if (i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
            }
            return ans;
        };
        // z函数 模板
        int ans = 0;
        vector<int> z1 = zFunc(0);
        for (int i = 0; i<n-2; i++) {   // nums1 : nums[0~i] i+1 即为 nums1 的长度
            vector<int> z2 = zFunc(i+1);
            if (z1[i+1] >= i+1) { // nums1 [0~i] 是 nums2 [i+1,2*i] .. [i+1..n-2] 前缀
                ans += n - 2 * (i+1);
                for (int j=i+2; j<min(2*(i+1),n); ++j) {  // nums2.len < i + 1 是否是nums3 的前缀
                    if (j-i-1 > n-j) break; // 前缀大于后缀
                    if (z2[j-i-1] >= j-i-1) ans ++;
                }                
            } else {  // 检查 nums2 是不是 nums3 的前缀
                for (int j=i+2; j<n; ++j) {
                    if (j-i-1 > n-j) break; // 前缀大于后缀
                    if (z2[j-i-1] >= j-i-1) ans ++;
                }
            }
        }

        return ans;        
    }
};

int main() {
    vector<int> nums = {1,1,0,1,3,2,2,2};
    cout << Solution().beautifulSplits(nums) << endl; 
}
#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        // 自行解答
        int ans = INT_MAX, n = nums.size();

        for (int i=0; i<n; ++i) {
            while (i != nums[i]) {
                ans = min(ans, ans & nums[nums[i]] & nums[i]);
                swap(nums[i], nums[nums[i]]);
            }
        }
        
        return ans == INT_MAX ? 0 : ans;        
    }

    int sortPermutation2(vector<int>& nums) {
        // 参考题解，更严谨
        int ans = -1, n = nums.size();

        for (int i=0; i<n; ++i)
            if (i != nums[i]) ans &= nums[i];
        
        return max(0, ans);
    }

};
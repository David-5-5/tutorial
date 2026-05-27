#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int longestArithmetic(vector<int>& nums) {
        // 前后缀分解
        int n = nums.size();
        vector<int> suf(n, 1); suf[n-2] = 2;
        for (int i=n-3; i; i--) 
            if (2 * nums[i+1] == nums[i] + nums[i+2])
                suf[i] += suf[i+1];
            else suf[i] = 2;
        int ans = suf[1] + 1, pre = 1;
        for (int i=1; i<n-1; i++) {
            ans = max(ans, max(pre+1, suf[i+1]+1));
            if (i>=2 && i<=n-3) {
                if (nums[i-1]-nums[i-2] == nums[i+2] - nums[i+1] && 2 * (nums[i+2] - nums[i+1]) == nums[i+1] - nums[i-1])
                    ans = max(ans, pre + suf[i+1] + 1);
            }
            if (i<=n-3 && nums[i+1] - nums[i-1] == 2 * (nums[i+2] - nums[i+1])) ans = max(ans, suf[i+1] + 2);
            if (i>=2 && 2 * (nums[i-1] - nums[i-2]) == nums[i+1] - nums[i-1]) ans = max(ans, pre + 2);
            
            if (i>=2 && nums[i-1] - nums[i-2] == nums[i]-nums[i-1]) pre += 1;
            else pre = 2;
        }
        
        return max(ans, pre + 1);
    }


};
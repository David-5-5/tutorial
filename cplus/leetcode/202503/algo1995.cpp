#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int n = nums.size(), ans = 0;

        for (int i=2; i<n; ++i) cnt[nums[i]]++;

        for (int i=2; i<n; ++i) {
            cnt[nums[i]] --;
            for (int j=1; j<i; ++j) {
                for (int k=0; k<j; ++k) {
                    int v = nums[i]+nums[j]+nums[k];
                    ans += cnt[v];
                }
            }
        }
        return ans;  
    }


    int countQuadruplets2(vector<int>& nums) {
        // 参考题解 nums[a] + nums[b] + nums[c] == nums[d] 
        // nums[a] + nums[b] == nums[d] - nums[c]
        // 遍历 nums[b] nums[c]
        unordered_map<int, int> cnt;
        int n = nums.size(), ans = 0;

        for (int c=2; c<n-1; c++) {
            int b = c-1;
            for (int a=0; a<b; a++) {           // 遍历 a
                cnt[nums[a]+nums[b]] ++;
            }
            
            for (int d=c+1; d<n; d++) {         // 遍历 d
                ans += cnt[nums[d]-nums[c]];
            }

        }
        return ans;  
    }
};
#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // 自行解答，前缀和 + 哈希表
        int n = nums.size(), ans = 0;

        vector<int> pres(n+1);
        unordered_map<int, int> cnt;

        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];
        for (auto& v : pres) {
            ans += cnt[v-goal];

            cnt[v] ++;
        }
        return ans;
    }


    int numSubarraysWithSum2(vector<int>& nums, int goal) {
        // 自行解答，滑动窗口
        // 思维比较高，如何找到 l1 和 l2 ? 自己写不出来
        // 0    0  1  0  1  0  0  1
        // l1,2    r   
        // l1      l2    r
        // l1      l2       r
        //         l1    l2        r
        int n = nums.size(), ans = 0;

        int l1 = 0, l2 = 0, r = 0, sum1 = 0, sum2 = 0;
        while (r < n) {
            sum1 += nums[r];
            while (l1 <= r && sum1 > goal) {
                sum1 -= nums[l1++];
            }
            sum2 += nums[r];  // 递增
            while (l2<=r && sum2 >= goal) {
                sum2 -= nums[l2++];
            }
            ans += l2 - l1;
            r ++;
        }
        return ans;    
    }
};
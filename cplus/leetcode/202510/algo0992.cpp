#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.3.3 恰好型滑动窗口
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // 自行解答，套公式，两次滑动窗口
        int n = nums.size();

        auto distinct = [&](int limit) -> int {
            unordered_map<int, int> cnt;
            int l = 0, ans = 0;

            for (int r=0; r<n; ++r) {
                cnt[nums[r]] += 1;
                
                while (cnt.size() >= limit) {
                    cnt[nums[l]] --;
                    if (cnt[nums[l]] == 0) cnt.erase(nums[l]);
                    l ++;
                }
                ans += l;
            }
            return ans;
        };
        return distinct(k) - distinct(k+1);
    }

    int subarraysWithKDistinct2(vector<int>& nums, int k) {
        // 自行解答，一次滑动窗口
        
    }    
};
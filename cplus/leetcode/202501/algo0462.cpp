#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 中位数贪心
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        // 自行解答
        int m = nums.size() >> 1;
        
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        for (auto v : nums)
            ans += abs(v - nums[m]);
        
        return ans;
    }

    int minMoves2_qs(vector<int>& nums) {
        // 自行解答
        auto qs = [&] (this auto&& qs, int l, int r, int k) -> int {
            if (l == r) return nums[k];
            auto pivot = nums[l]; auto i = l-1, j = r+1; 
            while (i < j) {
                do i++; while (nums[i] < pivot);
                do j--; while (nums[j] > pivot);
                if (i < j) swap(nums[i], nums[j]);
            }

            if (k<=j) return qs(l, j, k);
            else return qs(j+1, r, k);
        };

        int n = nums.size(); 
        int median = qs(0, n-1, n/2);
        int ans = 0; for(auto v:nums) ans += abs(v-median);
        return ans;
    }  

    int minMoves2_nth(vector<int>& nums) {
        // 自行解答
        int n = nums.size(); 
        nth_element(nums.begin(), nums.begin() + n/2, nums.end());
        int median = nums[n/2];
        int ans = 0; for(auto v:nums) ans += abs(v-median);
        return ans;
    }    
};
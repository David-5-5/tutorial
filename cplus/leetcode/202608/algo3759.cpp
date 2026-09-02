#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        map<int, int, greater<int>> cnt;
        for (auto v: nums) cnt[v] ++;
        
        int gr_cnt = 0, ans = 0;
        for (auto [_, v]: cnt) {
            if (gr_cnt >= k) ans += v;
            gr_cnt += v;
        }
        return ans;
    }

    int countElements(vector<int>& nums, int k) {
        if (k == 0) return nums.size();

        sort(nums.rbegin(), nums.rend());
        int gr_cnt = 0, prev = nums[0], cur_cnt = 0, ans = 0;
        for (auto v : nums) {
            if (prev == v) cur_cnt ++;
            else {
                gr_cnt += cur_cnt;
                prev = v; cur_cnt = 1;
            }
            if (gr_cnt >= k) ans ++;
        }
        
        return ans;
    }    

    int countElements(vector<int>& nums, int k) {
        // nth_element 用法
        int n = nums.size(), ans = 0;

        if (k == 0) return n;
        nth_element(nums.begin(), nums.begin() + n - k, nums.end());
        int kth = nums[n-k];
        for (auto & x: nums) {
            ans += x < kth;
        }
        
        return ans;
    }       
};
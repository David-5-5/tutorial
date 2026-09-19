#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        // 内置方法
        sort(nums.begin(), nums.end());

        int n = nums.size(), ans = 0;
        for (int i=1; i<n; i++) {
            ans = max(ans, nums[i] - nums[i-1]);
        }
        return ans;        
    }

    int maximumGap2(vector<int>& nums) {
        // 基数排序
        int n = nums.size(); long long exp = 1; if (n < 2) return 0;
        vector<int> buf(n) ;

        // auto mx = ranges::max(nums);
        auto mx = *max_element(nums.begin(), nums.end());
        
        while (mx >= exp) {
            int cnt[10] = {0};
            for (auto &v : nums) {
                cnt[v / exp % 10] ++;
            }
            for (int i=1; i<10; i++) cnt[i] += cnt[i-1];
            
            for (int i=n-1; i>=0; i--) {
                auto & v = nums[i];
                buf[--cnt[v/exp % 10]] = v;
            }
            copy(buf.begin(), buf.end(), nums.begin());
            exp *= 10;
        }
        
        int ans = 0;
        for (int i=1; i<n; i++) {
            ans = max(ans, nums[i] - nums[i-1]);
        }
        return ans;
    }


};
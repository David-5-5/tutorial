#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        // 二分 + 滑动窗口
        int n = nums.size(); 
        long long k = ((1LL * n * (n + 1) / 2) + 1) / 2;

        auto check = [&](int upper) -> bool {
            int l = 0;
            long long cnt = 0;
            unordered_map<int, int> freq;
            for (int r=0; r<n; ++r) {
                freq[nums[r]] ++;
                while (freq.size() > upper) {
                    freq[nums[l]] --;
                    if (freq[nums[l]] == 0) freq.erase(nums[l]);
                    l += 1;
                }
                cnt += r - l + 1;
                if (cnt >= k) return true;  // 注意条件
            }
            return false;
        };

        set<int> distinct(nums.begin(), nums.end());
        int l = 0, r = distinct.size();
        while (l+1 < r) {
            int mid = (l + r) / 2;
            (check(mid)? r:l) = mid;
        }
        return r;

    }
};
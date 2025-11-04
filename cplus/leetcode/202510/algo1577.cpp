#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答，双指针
        sort(nums1.begin(), nums1.end()); sort(nums2.begin(), nums2.end());

        auto count = [](vector<int>& square, vector<int>& pairs) -> int {
            int res = 0; 
            for (auto v : square) {
                long long sq_v = 1LL * v * v; int l = 0, r = pairs.size() - 1;
                while (l < r) {
                    long long multi = 1LL * pairs[l] * pairs[r];
                    if (multi < sq_v) {
                        l ++;
                    } else if (multi > sq_v) {
                        r --;
                    } else { // equals
                        if (pairs[l] == pairs[r]) {
                            res += (r-l)*(r-l+1)/2;
                            l = r;
                        } else {
                            int left = 1, right = 1;
                            while (pairs[l]==pairs[l+1]) left++, l++;
                            while (pairs[r]==pairs[r-1]) right++, r--;
                            res += left * right;
                            l++, r--;
                        }
                    }
                }
            }
            return res;
        };

        return count(nums1, nums2) + count(nums2, nums1);    

    }
};
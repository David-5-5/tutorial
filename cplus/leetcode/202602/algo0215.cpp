#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 快速选择算法 - 模板
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
        return qs(0, n-1, n-k);
    }
};
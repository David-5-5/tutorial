#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // 手写归并排序
        auto merge = [&] (this auto&& merge, int l, int r) {
            if (l + 1 == r) return;
            auto mid = (l + r) / 2;
            merge(l, mid); merge(mid ,r);

            vector<int> larr(nums.begin()+l, nums.begin()+mid);
            vector<int> rarr(nums.begin()+mid, nums.begin()+r);
            int j = l, p1 = 0, p2 = 0;
            while (p1 < larr.size() && p2 < rarr.size()) {
                if (larr[p1] <= rarr[p2])  nums[j++] = larr[p1++];
                else nums[j++] = rarr[p2++];
            }

            while (p1 < larr.size()) nums[j++] = larr[p1++];
            while (p2 < rarr.size()) nums[j++] = rarr[p2++];
        };
        
        merge(0, nums.size());
        return nums;          
    }
};
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        int n = nums.size();
        for (int i=0; i<n/2; i++) {
            ans.emplace_back(nums[i]);
            ans.emplace_back(nums[(n+1)/2 + i]);
        }
        if (n%2) ans.emplace_back(nums[n/2]);
        nums = move(ans);

    }

    void wiggleSort2(vector<int>& nums) {
        // 原地修改
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int l = 1, r = (n+1)/2;
        while (l < r) {
            swap(nums[l], nums[r]);
            l += 2; r++;
        }
    }
};



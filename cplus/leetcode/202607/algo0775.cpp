#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int suf_mn = INT_MAX, n = nums.size();
        for (int i=n-2; i>=0; i--) {
            if (nums[i] > suf_mn) return false;
            suf_mn = min(nums[i+1], suf_mn);
        }

        return true;
    }
};
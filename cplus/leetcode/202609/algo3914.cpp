#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums) {
        long long x_sum = 0; int n = nums.size();
        for (int i=n-1; i; i--) {
            x_sum += max(0, nums[i-1]-nums[i]);
        }

        return x_sum;
    }
};
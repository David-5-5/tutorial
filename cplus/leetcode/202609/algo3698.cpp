#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size(); long long left = 0, right = 0;

        int i=0, j=n-1;
        while (i+1<n && nums[i] < nums[i+1]) {
            left += nums[i]; i++;
        }
    
        while (j && nums[j-1] > nums[j]) {
            right += nums[j]; j--;
        }

        // 有效情况: 
        // i == j   nums[i-1] < nums[i] && nums[i] > nums[i+1]
        // i+1 == j nums[i-1] < nums[i] == nums[j] > nums[j+1]
        if (j-i > 1) return -1; 

        return i==j?min(abs(left+nums[i]-right), abs(right+nums[i]-left)):abs(left-right);
    }
};
#include <bits/stdc++.h>
using namespace std;

// 力扣周赛 384
class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int n = nums.size(), m = pattern.size(), ans = 0;
        for (int i=0; i<n-m; i++) {
            bool match = true;
            for (int k=0; k<m; k++) {
                if (!(pattern[k]== 1 && nums[i+k+1] > nums[i+k] ||
                    pattern[k]== 0 && nums[i+k+1] == nums[i+k]||
                    pattern[k]== -1 && nums[i+k+1] < nums[i+k])) {
                        match=false;
                        break;
                    } 
            }
            if (match) ans ++;
        }
        return ans;
    }
};

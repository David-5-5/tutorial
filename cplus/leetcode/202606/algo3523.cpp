#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        int last = nums[0], ans = 1, n = nums.size();
        for (int i=1; i<n; i++) {
            if (nums[i] >= last) {
                last = nums[i]; ans += 1;
            }
        }
        return ans;
    }
};
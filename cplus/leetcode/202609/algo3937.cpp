#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int ans = INT_MAX, n = nums.size();

        for (int x=0; x<k; x++) for (int y=0; y<k; y++) {
            int res = 0;
            if (y == x) continue;
            for (int i=0; i<n; i++) {
                if (i % 2) res += min(k-abs(y-nums[i] % k), abs(y - nums[i] % k));
                else res += min(k-abs(x-nums[i] % k), abs(x - nums[i] % k));
            }
            ans = min(ans, res);
        }
        return ans;
    }
};
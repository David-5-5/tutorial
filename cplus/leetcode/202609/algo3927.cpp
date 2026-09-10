#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minArraySum(vector<int>& nums) {
        long long ans = 0; int n = nums.size(); set<int> factors;
        sort(nums.begin(), nums.end());
        if (nums[0] == 1) return n;

        for (auto x: nums) {
            bool found = false; int mx = sqrt(x), cand = INT_MAX;
            for (int i=2; i<=mx; i++) {
                if (x % i == 0) {
                    if (factors.count(i)) {found = true; ans += i; break;}
                    else if (factors.count(x / i)) cand = x / i;
                }
            }
            if (!found) {
                if (cand < INT_MAX)
                    ans += cand; 
                else {ans += x;  factors.insert(x);}
            }
        }
        return ans;
    }
};
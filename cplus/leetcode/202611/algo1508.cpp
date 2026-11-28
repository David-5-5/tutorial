#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        const int mod = 1e9 + 7;
        vector<int> subsum;
        for (int i=0; i<n; i++) {
            int pres = 0;
            for (int j=i; j<n; j++) {
                pres += nums[j]; subsum.emplace_back(pres);
            }
        }
        sort(subsum.begin(), subsum.end());
        long long ans = 0;
        for (int i=left-1; i<right; i++) ans += subsum[i];
        return ans % mod;
    }
};
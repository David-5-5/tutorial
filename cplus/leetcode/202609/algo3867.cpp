#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        // 模拟，按照题目写代码
        long long ans = 0; int mx = 0;
        vector<int> prefixGcd;
        for (auto & v: nums) {
            mx = max(mx, v);
            prefixGcd.emplace_back(gcd(mx, v));
        }

        sort(prefixGcd.begin(), prefixGcd.end());
        int n = prefixGcd.size();
        for (int i=0; i<n/2; i++) {
            ans += gcd(prefixGcd[i], prefixGcd[n-1-i]);
        }
        return ans;
    }
};
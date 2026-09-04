#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumScore(vector<int>& nums, string s) {
        long long ans = 0; int n = nums.size();
        priority_queue<int> pq;

        for (int i=0; i<n; i++) {
            pq.emplace(nums[i]);
            if (s[i] == '1') {
                ans += pq.top(); pq.pop();
            }
        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int centeredSubarrays(vector<int>& nums) {
        // 自行解答 暴搜
        int ans = 0, n = nums.size();
        for (int i=0; i<n; i++) {
            unordered_set<int> n_hash; int pres = 0;
            for (int j=i; j<n; j++) {
                pres += nums[j]; n_hash.insert(nums[j]);
                if (n_hash.count(pres)) ans ++;
            }
        }

        return ans;
    }
};
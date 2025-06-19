#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        // 自行解答
        int n = nums.size(), sufs = 0, mids = 0, pres = 0;
        for (int i=0; i<k; ++i) {
            pres += nums[i];
            mids += nums[k+i];
            sufs += nums[n-1-i];
        }

        vector<pair<int, int>> suf_mx(n-k+1);

        suf_mx[n-k] = {sufs, n-k};
        for (int i=n-k-1; i; --i) {
            sufs += nums[i] - nums[i+k];
            if (sufs >= suf_mx[i+1].first) {
                suf_mx[i] ={sufs, i};
            } else suf_mx[i] = suf_mx[i+1];
        }
        int pre_inx = 0, pre_mx = pres;
        int max_sum = 0; vector<int> ans = {0,0,0};
        for (int i=k; i<=n-2*k; ++i) {
            if (pre_mx + mids + suf_mx[i+k].first > max_sum) {
                max_sum = pre_mx + mids + suf_mx[i+k].first;
                ans = {pre_inx, i, suf_mx[i+k].second};
            }
            mids += nums[i+k] - nums[i];
            pres += nums[i] - nums[i-k];
            if (pre_mx < pres){
                pre_mx = pres;
                pre_inx = i - k + 1;
            }
        }

        return ans;
    }
};
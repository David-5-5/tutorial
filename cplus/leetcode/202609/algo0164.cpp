#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        // 内置方法
        sort(nums.begin(), nums.end());

        int n = nums.size(), ans = 0;
        for (int i=1; i<n; i++) {
            ans = max(ans, nums[i] - nums[i-1]);
        }
        return ans;        
    }

    int maximumGap2(vector<int>& nums) {
        // 基数排序
        int n = nums.size(); long long exp = 1; if (n < 2) return 0;
        vector<int> buf(n) ;

        // auto mx = ranges::max(nums);
        auto mx = *max_element(nums.begin(), nums.end());
        
        while (mx >= exp) {
            int cnt[10] = {0};
            for (auto &v : nums) {
                cnt[v / exp % 10] ++;
            }
            for (int i=1; i<10; i++) cnt[i] += cnt[i-1];
            
            for (int i=n-1; i>=0; i--) {
                auto & v = nums[i];
                buf[--cnt[v/exp % 10]] = v;
            }
            copy(buf.begin(), buf.end(), nums.begin());
            exp *= 10;
        }
        
        int ans = 0;
        for (int i=1; i<n; i++) {
            ans = max(ans, nums[i] - nums[i-1]);
        }
        return ans;
    }

    int maximumGap3(vector<int>& nums) {
        // 桶排序
        auto mx = *max_element(nums.begin(), nums.end());
        auto mn = *min_element(nums.begin(), nums.end());
        int n = nums.size(); if (n < 2) return 0;
        int d = max(1, (mx - mn)/(n-1)); int bucketSize = (mx-mn) / d + 1;
        vector<pair<int, int>> bucket(bucketSize, {-1, -1});
        for (auto & v: nums) {
            int idx = (v - mn) / d;
            if (bucket[idx].first == -1) {
                bucket[idx].first = bucket[idx].second = v;
            } else {
                bucket[idx].first = min(bucket[idx].first, v);
                bucket[idx].second = max(bucket[idx].second, v);
            }
        }
        int ans = 0, prev = -1;
        for (int i=0; i<bucketSize; i++) {
            if (bucket[i].first == -1) continue;
            if (prev != -1) {
                ans = max(ans, bucket[i].first - bucket[prev].second);
            }
            prev = i;
        }
        return ans; 
    }
};
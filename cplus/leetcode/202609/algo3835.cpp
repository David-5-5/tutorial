#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        // 性能比较 multiset 576
        long long ans = 0; int l = 0, n = nums.size();
        multiset<int> sorted;
        for (int r=0; r<n; r++) {
            sorted.insert(nums[r]);
            while (!sorted.empty() && 1LL * (r-l+1) * (*sorted.rbegin()-*sorted.begin()) > k) {
                auto it = sorted.find(nums[l++]); sorted.erase(it);
            }
            ans += r - l + 1;
        }

        return ans;     
    }

    long long countSubarrays(vector<int>& nums, long long k) {
        // 性能比较 map 653
        long long ans = 0; int l = 0, n = nums.size();
        map<int, int> sorted;
        for (int r=0; r<n; r++) {
            sorted[nums[r]] ++;
            while (!sorted.empty() && 1LL * (r-l+1) * (sorted.rbegin()->first-sorted.begin()->first) > k) {
                sorted[nums[l]] --; 
                if (sorted[nums[l]] == 0) sorted.erase(nums[l]);
                l++;
            }
            ans += r - l + 1;
        }

        return ans;   
    }

    long long countSubarrays(vector<int>& nums, long long k) {
        // 性能比较 deque
        long long ans = 0; int l = 0, n = nums.size();
        deque<int> sorted;
        for (int r=0; r<n; r++) {
            sorted[nums[r]] ++;

            ans += r - l + 1;
        }

        return ans;   
    }    
};
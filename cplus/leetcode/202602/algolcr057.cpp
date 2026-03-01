#include <bits/stdc++.h>
using namespace std;

// 同 220
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        // 滑动窗口
        set<pair<int, int>> vi; int n = nums.size(); if (n < 2) return false;
        vi.insert({nums[0], 0});

        for (int i=1; i<n; ++i) {
            auto it = vi.lower_bound({nums[i]-valueDiff, i-min(indexDiff, i)});
            if ((it!=vi.end() && it->first <= nums[i]+valueDiff) ||
                    (it == vi.end() &&vi.rbegin()->first >= nums[i]-valueDiff) ) return true;
            
            if (vi.size()==indexDiff) vi.erase({nums[i-indexDiff], i-indexDiff});
            vi.insert({nums[i], i});
        }
        
        return false; 
    }
};


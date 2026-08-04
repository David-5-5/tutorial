#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size(); 
        vector<pair<int, int>> miss;
        
        int l = -1, mx_diff = 0, mx_val = nums[0];
        for (int i=1; i<n; i++) {
            if (nums[i-1] == -1 && nums[i] != -1) miss.emplace_back(l, i);
            else if (nums[i-1] != -1 && nums[i] == -1) l = i-1;
            else if (nums[i-1] != -1 && nums[i] != -1) mx_diff = max(mx_diff, abs(nums[i-1]-nums[i]));
            mx_val = max(mx_val, nums[i]);
        }
        if (mx_val == -1) return 0;

        if (nums[n-1] == -1) miss.emplace_back(l, -1);

        auto check = [&](int limit) -> bool {
            if (miss.size() == 1 && miss[0].first == -1 && miss[0].second == -1) return true;
            vector<pair<int, int>> intervals;

            for (auto [l, r]: miss) {
                if (l == -1) intervals.emplace_back(nums[r]-limit, nums[r]+limit);
                else if (r == -1) intervals.emplace_back(nums[l]-limit, nums[l]+limit);
                else {
                    auto a = min(nums[l], nums[r]), b = max(nums[l], nums[r]);
                    if (l + 2 == r) {
                        // 剪枝，性能影响不大
                        // if (b - a > 2 * limit) return false;
                        intervals.emplace_back(b-limit, a+limit);
                    } else {
                        // if (b - a > 3LL * limit) return false;
                        intervals.emplace_back(a-limit, a+limit);
                        intervals.emplace_back(b-limit, b+limit);
                    }   
                }
            }
            auto x = INT_MAX; int y = 0;
            for (auto& [left, right] : intervals) {
                x = min(x, right); y = max(left, y);
            }

            if (x >= y) return true;
            for (auto [left, right] : intervals) {
                if ((x < left || x > right) && (y < left ||right < y)) return false;
            }
            auto validate = [&](int l, int r) -> bool {            
                if (l == -1) {
                    if (abs(nums[r] - x) <= limit || abs(nums[r] - y) <= limit) return true;
                } else if (r == -1) {
                    if (abs(nums[l] - x) <= limit || abs(nums[l] - y) <= limit) return true;
                } else {
                    if ((abs(nums[l] - x) <= limit && abs(nums[r] - x) <= limit) || 
                        (abs(nums[l] - y) <= limit && abs(nums[r] - y) <= limit)) return true;
                    if (l + 2 < r) {
                        auto a = min(nums[l], nums[r]), b = max(nums[l], nums[r]);
                        if (abs(a-x) <= limit && abs(b-y) <= limit && y-x<=limit) return true;
                    }
                }
                return false;
            };

            for (auto [l, r]: miss) if(!validate(l, r)) return false; 
            return true;
        };

        int left = mx_diff-1, right = mx_val + 1;
        while (left + 1 < right) {
            auto mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;    
    }
  
};

int main() {
    vector<int> nums = {14,-1,-1,46};
    Solution().minDifference(nums);
}
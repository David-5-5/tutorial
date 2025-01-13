#include <bits/stdc++.h>
using namespace std;

// 周赛 382
class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        // int mx = ranges::max(nums);
        int bits = 5;

        auto to_and = [&](int b) -> int {
            int n = nums.size();
            if (k == 0) return 0;
            int cnt = 0, first = -1;
            for (int i=0; i<n; i++) {
                if (nums[i] >> b & 1) cnt += 1;
                else if (first == -1) first = i;
            }
            if (cnt == 0 || cnt > k) return 0;

            vector<int> tmp;
            if (first > 0) {
                for (int i=0; i<first; i++) {
                    nums[first] &= nums[i];
                }
            }
            tmp.push_back(nums[first]);
            for (int i=first+1; i<n; i++) {
                if (nums[i] >> b & 1) 
                    if (i+1 >= n || nums[i+1]>>b & 1) tmp.back() &= nums[i];
                    else{
                        int a = (nums[i+1] & nums[i])|tmp.back();
                        int b = nums[i+1]|(nums[i]&tmp.back());
                        if (a < b)
                            nums[i+1] &= nums[i];
                        else tmp.back() &= nums[i];
                    }
                else tmp.push_back(nums[i]);
            }
            nums = tmp;
            return cnt;
        };

        for (int b=bits; b>=0; b--)  k -= to_and(b);

        int ans = 0;
        for (auto v : nums) ans |= v;
        return ans;
    }
};

int main() {
    Solution sol;
    // vector<int> nums = {37,6,46,32,23};
    vector<int> nums = {7,3,15,14,2,8};
    cout << sol.minOrAfterOperations(nums, 4);
}
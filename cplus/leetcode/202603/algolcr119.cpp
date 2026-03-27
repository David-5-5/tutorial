#include <bits/stdc++.h>
using namespace std;

// 同 128
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 参考题解 O(N) 从最小的 x 开始遍历
        unordered_set<int> n_set(nums.begin(), nums.end());

        int ans = 0; 
        for (auto x: n_set) {
            if (!n_set.count(x-1)) {
                int res = 1;
                while (n_set.count(++x)) res ++;
                ans = max(ans, res);
            }
        }

        return ans;    
    }
};
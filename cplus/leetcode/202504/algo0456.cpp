#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.2 枚举中间
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        // 自行解答，有这个思路都不敢写，题解的第一种方法和思路的一致。
        // 枚举 3
        int n = nums.size();
        vector<int> suf;
        for (int i=2; i<n; i++) suf.push_back(nums[i]);

        sort(suf.begin(), suf.end());
        
        int pre = nums[0];
        for (int i=1; i<n-1; i++) {
            if (pre < nums[i]) {
                int inx = ranges::lower_bound(suf, nums[i]) - suf.begin();
                if (inx && suf[inx-1] > pre) return true;
            }
            pre = min(pre, nums[i]);
            suf.erase(ranges::lower_bound(suf, nums[i+1]));
        }

        return false;       
    }

    bool find132pattern2(vector<int>& nums) {
        // 参考题解 枚举 2
        int n = nums.size();
        stack<int> can_k;
        can_k.push(nums[n-1]);
        int max_k = INT_MIN;

        for (int i=n-2; i>=0; i--) {
            if (nums[i] < max_k) return true;

            while (!can_k.empty() && nums[i] > can_k.top()) {
                max_k = max(max_k, can_k.top());
                // max_k = can_k.top();     // it is also ok ?
                can_k.pop();
            }

            if (nums[i] > max_k) can_k.push(nums[i]);
        }

        return false;
    }
};
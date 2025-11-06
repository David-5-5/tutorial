#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.2 同向双指针
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        int pre = 0, suf = n-1;
        while (suf > 0 && nums[suf-1] <= nums[suf]) suf --;
        if (suf == 0) return 0; // 全有序

        while (pre+1 < n && nums[pre] <= nums[pre+1]) pre++;
        multiset<int> midpoint;

        // 若非全有序，将 [pre, suf] 之间的值加入队列
        for (int i=pre; i<=suf; ++i) midpoint.insert(nums[i]);
        while (pre>0 && *midpoint.begin()<nums[pre-1]) pre--;
        while (suf+1<n && *midpoint.rbegin()>nums[suf+1]) suf++;
        return suf - pre + 1;    
    }

    int findUnsortedSubarray2(vector<int>& nums) {
        // 自行解答 - 优化用 mx mn 代替set 或
        int n = nums.size();
        int pre = 0, suf = n-1;
        while (suf > 0 && nums[suf-1] <= nums[suf]) suf --;
        if (suf == 0) return 0; // 全有序

        while (pre+1 < n && nums[pre] <= nums[pre+1]) pre++;
        int mn = INT_MAX, mx = INT_MIN;

        // 若非全有序，将 [pre, suf] 之间的值加入队列
        for (int i=pre; i<=suf; ++i) mn = min(mn, nums[i]), mx = max(mx, nums[i]);
        while (pre>0 && mn<nums[pre-1]) pre--;
        while (suf+1<n && mx>nums[suf+1]) suf++;
        return suf - pre + 1;   
    }    
};
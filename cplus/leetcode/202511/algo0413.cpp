#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        // 自行解答
        int n = nums.size(), i = 0, ans = 0;
        if (n < 3) return ans;
        while (i < n-2) {
            int start = i;
            i ++;
            while (i < n-1 && nums[i]-nums[i-1] == nums[i+1]-nums[i]) i++;
            // 两个数比较的情况 i 即为不等于分组的数 i - start 为分组的数量
            // 本题 i+1 是等差数组下一个数，i - start + 1 是等差队列的长度
            if (i+1 - start >= 3) {
                ans += (i+1-start-2) * (i+1-start-1) / 2;
            }
        }
        return ans;
    }
};
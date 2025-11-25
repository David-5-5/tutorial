#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        // 自行解答 可作为 分组循环 的 模板
        long long ans = 0;
        int i = 0, n = nums.size();
        while (i < n) {
            if (nums[i] == 0) {
                int j = i;
                while (i<n && nums[i] == 0) ans += i-j+1, i++;
            } else i ++;
        }
        return ans;   
    }
};
#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 参考题解，很简单的题目，很有技巧
        int n = nums.size();
        if (n <= 2) {
            return n;
        }
        int st_size = 2;
        for (int i=2; i<n; i++) {
            if (nums[i]!=nums[st_size-2]) {
                nums[st_size++] = nums[i];

            }
        }
        return st_size;
    }
};

int main() {
    vector<int> nums = {1,1,1,2,2,3};
    cout << Solution().removeDuplicates(nums);
}
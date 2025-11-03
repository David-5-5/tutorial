#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        // 自行解答，用栈
        stack<int> odd, even; int n = nums.size();
        for (int i=0; i<n; ++i) {
            if ((nums[i] % 2) ^ (i % 2)) {
                
                if (i%2) {
                    if (odd.size()) swap(nums[i], nums[odd.top()]), odd.pop();
                    else even.push(i);
                } else {
                    if (even.size()) swap(nums[i], nums[even.top()]), even.pop();
                    else odd.push(i);
                }
            }
        }
        return nums;     
    }


};
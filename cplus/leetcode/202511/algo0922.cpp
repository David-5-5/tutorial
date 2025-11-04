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

    vector<int> sortArrayByParityII(vector<int>& nums) {
        // 自行解答，双指针
        int even = 0, odd = 1, n = nums.size();
        while (even < n) {
            while (even < n && nums[even] % 2 == 0) even += 2;
            if (even >= n) break;
            while (nums[odd] % 2) odd += 2;            
            swap(nums[even], nums[odd]);
            even += 2, odd += 2;
            
        }
        return nums;    
    }    
};
#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    int minDeletion(vector<int>& nums) {
        // 自行解答
        int i = 0, j = 1, ans = 0, n = nums.size();
        
        while (i<n) {
            while (j<n && nums[i]==nums[j]) ans ++, j++;
            if (j == n) {
                ans += 1;
            }
            i = j + 1;
            j = i + 1;
        }
        return ans;
    }
};
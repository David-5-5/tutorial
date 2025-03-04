#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        // 记忆化搜索见py  O(n^2)
        // O(n) 动态规划优化
        int n = nums.size();

        if (n<2) return n;

        int down = 1, up = 1;   // 初始化 nums[0] 为结尾的上升或下降序列的长度
        for (int i=1; i<n; i++) {
            if (nums[i] > nums[i-1]) {
                up = max(up, down+1);           // 转移方程 i-1为结尾 的上升序列和 i-1 为结尾的下降序列 
            } else if (nums[i] < nums[i-1]) {
                down = max(down, up+1);         // 转移方程
            }
        }

        return max(up, down);         
    }
};
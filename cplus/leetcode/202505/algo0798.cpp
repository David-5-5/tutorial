#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int bestRotation(vector<int>& nums) {   
        // 参考题解
        // https://leetcode.cn/problems/smallest-rotation-with-highest-score/solutions/941834/798-czhong-gui-zhong-ju-de-chai-fen-jie-4o0yr/
        // 对于num，它位于 [num, n-1]里是能得分的， 基于现在数值，我们就能知道它的有效区间是什么
        // 开始的点+1，结束的点-1
        // 范围是 [i+1, n+i+1-nums[i]]: 这里要注意范围溢出，所以会用n来取模
        // 计算出差分数组后，单次遍历不断累加取最大结果就是答案

        int n = nums.size();
        int diff[n];
        memset(diff, 0, sizeof(diff));
        for (int i = 0; i < n; ++i)
        {
            ++diff[(i+1)%n];
            --diff[(n+i+1-nums[i])%n];
        }

        int res = 0;
        int currScore = 0;
        int maxScore = INT_MIN;
        for (int i = 0; i < n; ++i)
        {
            currScore += diff[i];
            if (currScore > maxScore)
            {
                maxScore = currScore;
                res = i;
            }
        }

        return res;
    }
};
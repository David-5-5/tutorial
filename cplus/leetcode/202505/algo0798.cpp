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
        
        // nums 数组向左旋转，向左旋转的距离为 k = 0 ~ n - 1 共 n 次
        // 令 x = nums[i] 当 (i - k + n)%n - x  >= 0 时， 计数为 1，
        // 因此需要求出 k = 0 ~ n - 1，
        // 每个 x， (i - k + n)%n - x  >= 0 时， k 的取值范围
        //          当 i >= k 时 i - k - x >= 0  ->  k <= min(i-x) where i-x >= 0;
        //          当 i < k 时，n + i - k  - x >=0   ->  i < k < n+i-x -> i+1<=k<=n+i-x
        // 综上 i+1<=k<=(n+i-x) % n
        // 通过差分数组对于每个 x， diff[k_begin] +=1 , diff[k_end+1] -= 1
        // 最后求出差分前缀和的最大值的最小的inx

        int n = nums.size();
        int diff[n];
        memset(diff, 0, sizeof(diff));
        for (int i = 0; i < n; ++i)
        {
            ++diff[(i+1)%n];
            --diff[(n+i+1-nums[i])%n];  // +1 差分的要求
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
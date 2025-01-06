#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 数学贪心 - 乘积贪心
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        // 自行解答 贪心
        int first = -1, second = -1;
        int cur = 0, ans = 0, cnt = 0;

        for (int i=0; i < nums.size(); i++) {
            if (nums[i] == 0) { // 复位
                first = second = -1;
                cnt = cur = 0;
            } else if (nums[i] < 0) {
                cnt = (cnt + 1) % 2;
                if (cnt == 1) { // first 为第一次出现负数后的前序正数的下标
                    if (first == -1) first = i-cur;
                    // 与前序匹配成偶数负数后形成的最长子数组长度
                    if (second != -1) cur = i - second + 1; 
                    else cur = 0;
                } else { // second 为第二次出现负数后的前序正数的下标
                    if (second == -1) second = i-cur;
                    // 与前序匹配成偶数负数后形成的最长子数组长度
                    cur = i - first + 1;
                }

            } else cur += 1;
            ans = max(cur, ans);
        }

        return ans;  

    }

    int getMaxLen(vector<int>& nums) {
        // 官方题解 动态规划
        int n = nums.size();
        int positive[n]; // 表示以下标 i 为结尾的正数最长子数组长度
        int negative [n]; // 表示以下标 i 为结尾的负数最长子数组长度
        // 必须初始化数组
        memset(positive, 0, sizeof(positive));
        memset(negative, 0, sizeof(negative));

        // vector<int> positive(n), negative(n);
        
        if (nums[0] > 0) {
            positive[0] = 1;
        } else if (nums[0] < 0){
            negative[0] = 1;
        }
        int ans = positive[0];
        for (int i=1; i<n;i++) {
            if (nums[i] == 0) 
                positive[i] = negative[i] = 0;
            else if (nums[i] > 0) {
                positive[i] = positive[i-1] + 1;
                if (negative[i-1]) negative[i] = negative[i-1] + 1; // 负正得负
            } else {
                negative[i] = positive[i-1] + 1; // 正负得负
                if (negative[i-1]) positive[i] = negative[i-1] + 1; // 负负的正
            }
            ans = max(ans, positive[i]);
        }

        return ans; 

    }
};
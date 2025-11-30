#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int candy(vector<int>& ratings) {
        // 自行解答
        int i = 0, n = ratings.size();
        vector<int> ans(n);
        
        while (i < n) {
            int st = i;
            i ++;
            while (i < n && ratings[i-1] >= ratings[i]) i++;
            ans[i-1] = 1;
            for (int j=i-2; j>=st; j--) {
                if (ratings[j] > ratings[j+1]) ans[j] = ans[j+1] + 1;
                // 难度在于深入理解题目，相邻的相等元素在非递增序列中
                // 倒序元素时，对于后一个是相等元素，可将元素设置为 1（坑）
                else ans[j] = 1; // ratings[j] == ratings[j+1]
            }
            if (st>0 && ans[st]<=ans[st-1]) ans[st] = ans[st-1] + 1;
        }
        return accumulate(ans.begin(), ans.end(), 0);
    }
};
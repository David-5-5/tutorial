#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        // 参考题解，枚举修改的元素，前后缀都是O(1)时间计算出结果
        int n = nums.size();
        vector<long> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];
        
        int ans = 0;
        unordered_map<long, int> left, right;
        // i 表示前缀数量 i < n-1, 后缀不为空，至少有一个
        for (int i=0; i<n-1; ++i) {         
            // right - left = total - left - left = total - 2*left
            long cnt = pres[n] - 2 * pres[i+1]; 
            right[cnt] ++;
            if (cnt == 0) ++ans;
            
        }

        // 遍历修改的值
        for (int i=0; i<n; ++i) {
            long cnt = pres[n] - 2 * pres[i+1];
            ans = max(ans, left[nums[i] - k] + right[k-nums[i]]);
            left[cnt]++;
            right[cnt] --;
        }

        return ans;

    }
};
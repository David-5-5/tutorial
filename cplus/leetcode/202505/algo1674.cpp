#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        // 参考题解,  有点烧脑
        // [+2 ... [-1]   [-1][+1]     [+1]  -2]
        // 令 a = nums[i], b = nums[n-1-i]
        // 更改 0 次区间 l0 = a + b = r0 
        // 更改 1 次区间 l1 = 1 + min(a,b), r1= limit+max(a,b)
        // 更改 2 次区间 l2 = 2, r2=  2 * limit
        // 区间的包含关系如下：
        // l2 <= l1  <= l0 <= r0 <= r1 <= r2        
        vector<int> diff(limit*2 + 2, 0);

        int n = nums.size(), m = n/2;

        for (int i=0; i<m; ++i) {


            // 默认所有区间使用差分修改 2 次
            diff[2] += 2;
            diff[2*limit + 1] -2;

            // 找出修改为一次的区间使用差分 -1 +1
            int l = 1 + min(nums[i], nums[n-1-i]);
            int r = limit + max(nums[i], nums[n-1-i]);
            diff[l] --;
            diff[r + 1] ++;

            // 找出修改为0的区间使用差分 -1 +1
            l = nums[i] + nums[n-1-i], r = l;
            diff[l] --;
            diff[r+1] ++;
        }

        int sum = 0, ans = INT_MAX;
        for (int i=2; i<=limit*2; ++i) {
            sum += diff[i];
            ans = min(ans, sum);
        }
        return ans;

    }
};
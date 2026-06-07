#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        // 自行解答 
        int n = nums.size(), val = 0;
        if (n == 2) return abs(nums[0] - nums[1]);
        if (n == 3) return nums[0] + nums[1] + nums[2] - 2 * ranges::min(nums);
    
        for (int i=1; i<n; i++) {
            val += abs(nums[i] - nums[i-1]);
        }
        int max_val = val;

        int pre_mn = max(nums[0], nums[1]);
        int pre_mx = min(nums[0], nums[1]);
        
        // 分析的思路比较难，无边界的情况下，翻转涉及 4 个元素，如果去除绝对值
        // 最大元素一定在翻转前后保持正数，最小元素一定保持为负数
        // 在如下情况下：
        // 翻转前，次大元素在翻转前为负数，次小元素翻转前为正数，
        // 翻转后，次大元素在翻转前为正数，次小元素翻转前为负数，
        // 这样对数组值的贡献为 2 * (次大元素 - 次小元素)
        // 遍历后两个元素 x3, x4
        // 只有 x1, x2 < x3, x4  或 x1 x2 > x3 x4 的情况下, 满足条件
        // x1, x2 < x3, x4 下找前缀中 pre_mn = min(pre_mn, max(x1, x2)) // 次小值的最小值
        // x1, x2 > x3, x4 下找前缀中 pre_mx = max(pre_mx, min(x1, x2)) // 次大值的最大值
        for (int i=3; i<n; i++) {
            int mn = min(nums[i-1], nums[i]), mx = max(nums[i-1], nums[i]);
            if (mn > pre_mn) max_val = max(max_val, val + 2 * (mn - pre_mn));
            if (mx < pre_mx) max_val = max(max_val, val + 2 * (pre_mx - mx));
            pre_mn = min(pre_mn, max(nums[i-1], nums[i-2]));
            pre_mx = max(pre_mx, min(nums[i-1], nums[i-2]));
        }

        // 边界情况，是否能和上面的情况合并，还需要进一步分析
        //nums[0..i]进行翻转 仅涉及三个元素
        //nums[i..n-1]进行翻转，仅涉及三个元素
        for (int i=2; i<n; i++) {   
            max_val = max(max_val, val + abs(nums[i]-nums[0]) - abs(nums[i]-nums[i-1]));
            max_val = max(max_val, val + abs(nums[n-1-i]-nums[n-1]) - abs(nums[n-1-i]-nums[n-i]));
        }

        return max_val;
    }
};
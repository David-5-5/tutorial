#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int minimumArrayLength(vector<int>& nums) {
        // 自行解答 - 计算 gcd 比较耗时

        // 自定义 gcd
        // function<int(int,int)> gcd = [&](int a, int b) -> int {
        //     return b == 0 ? a : gcd(b, a % b);
        // };
        
        unordered_map<int, int> cnt;
        int g = nums[0], n = nums.size();

        for (int i=0; i < n; i++) {
            g = gcd(g, nums[i]); // 调用自定义 gcd 或 std::gcd
            cnt[nums[i]] += 1;
        }

        return cnt[g] == 0 ? 1 : (cnt[g]+1) / 2;
    }

    int minimumArrayLength2(vector<int>& nums) {
        // 参考题解
        // 取最小值，对于其他数存在不是整除最小数的，返回 1
        // 例如 4,4,4 ..,4,4, 6, 8,...8, 6 % 4 得到 2
        // 可以将大于 2 的数全部 % 掉，最后剩下一个 2
        int m = ranges::min(nums);
        for (auto v : nums) {
            if (v % m) return 1;
        }

        return (ranges::count(nums,m) + 1) / 2; // 返回最小数计数除二上取整
    }
};